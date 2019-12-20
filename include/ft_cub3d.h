/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoudouy <acoudouy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 13:21:16 by acoudouy          #+#    #+#             */
/*   Updated: 2019/12/17 18:55:56 by acoudouy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef FT_CUB3D_H
# define FT_CUB3D_H

# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include "mlx.h"
# include <unistd.h>
# include <math.h>
# include "../libft/libft.h"
# include "keys.h"

// gcc -lmlx  -framework OpenGL -framework AppKit

/*
**	Definition du chemin des textures
*/

/*
# define NO "../texture/north.XPM"
# define SO "../texture/south.XPM"
# define WE "../texture/west.XPM"
# define EA "../texture/east.XPM"
*/

/*
**	Fonctions et structure pour la creation de la carte
*/

typedef struct	s_map
{
	int			width;
	int			height;
	char		**val;
}				t_map;

int				check_content_map(t_map *m);
t_map			read_map();

/*
**	Definition du player et de l'environnement variable
*/

# define path_map "../map/test.cub"
# define pos_X_start 150
# define pos_Y_start 150
# define angle_start 0
# define rotation 15
# define view 60.0f

int					check_res(int width, int height);

typedef struct 		s_player
{
	float			X;
	float			Y;
	float			angle;
	float			front;
	int				speed;
}					t_player;


/*
**	Fonctions et structure d'environnement
*/

# define res_width 640.0f
# define res_height 480.0f
# define sz_wall 64
# define cv_rad M_PI / 180
# define dist_plan ((res_width / 2.0f) / tan((cv_rad * view) / 2))

typedef struct		s_intersect
{
	float			X;
	float			Y;
	float			dist;
	char			orient;
}					t_intersect;

typedef struct		s_data
{
    void			*mlx_ptr;
    void			*mlx_win;
	float			res_w;
	float			res_h;
	t_player		player;
	t_map			*map;

}					t_data;

typedef struct 		s_wall
{
	t_intersect		pnt;
	float			width;
	float			height;
	char			card;
}					t_wall;

float				normalise_angle_ret(float angle);
int					deal_key(int key, t_data *data);

/*
**	Calcul des distances et des variables
*/

t_wall				ray_length_to_wall(t_data *data);

int					is_angle_x_neg(t_player player);
int					is_angle_y_neg(t_player player);
int					check_wall(t_data *data, t_intersect pnt);

/*
**	Picasso
*/

typedef struct		s_image
{
	void			*ptr;
	int				*data;
	int				bpp;
	int				endian;
	int				sz_line;
}					t_image;

void			draw_wall(t_data *data);
void			black_screen(t_data *data);

#endif
