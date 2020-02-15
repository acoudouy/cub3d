/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoudouy <acoudouy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 13:21:16 by acoudouy          #+#    #+#             */
/*   Updated: 2020/02/14 13:02:52 by acoudouy         ###   ########.fr       */
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

/*
** Etape pour les allocations de memoire
**-1 : erreur d'argument
** 0 : initialisation mlx, il ne faut pas les free
** 1 : malloc de la map
** 2 : malloc des lignes de la map
** 3 : malloc des colonnes de la map
** 4 : malloc des chemins des textures murs
** 5 : malloc de l'image data
** 6 : malloc de la liste de sprites
** 7 : malloc de l'image de sprites
*/

/*
**	Fonctions et structure pour la creation de la carte
*/

typedef struct		s_map
{
	int				width;
	int				height;
	char			**val;
	char			orient_start;
	int				x_start;
	int				y_start;
	int				check_pos;
}					t_map;

int					check_beginning_map(char *cont);
int					content_space(int i, char *cont);

/*
**	Definition du player et de l'environnement variable
*/

# define ROTATION 15
# define VIEW 60.0f

int					check_res(int width, int height);

typedef struct		s_player
{
	float			x;
	float			y;
	float			angle;
	float			front;
	int				speed;
}					t_player;

/*
**	Fonctions et structure d'environnement
*/

# define SZ_WALL 64
# define CV_RAD 0.01745329251

typedef struct		s_intersect
{
	float			x;
	float			y;
	float			dist;
	char			orient;
}					t_intersect;

typedef struct		s_image
{
	void			*ptr;
	int				*data;
	int				bpp;
	int				endian;
	int				sz_line;
	int				height;
	int				width;
	float			s_height;
	float			s_width;
	float			ratio;
}					t_image;

typedef struct		s_sprites
{
	t_intersect		pnt_spr;
	int				x_map;
	int				y_map;
	float			x_cent;
	float			y_cent;
	float			dist_cent;
	float			dist;
	float			height;
	char			card;
}					t_sprites;

typedef struct		s_lstspr
{
	t_sprites		*sprite;
	struct s_lstspr	*next;
}					t_lstspr;

typedef struct		s_args
{
	int				r;
	int				c;
	int				f;
	int				ea;
	int				no;
	int				so;
	int				we;
	int				s;
}					t_args;

typedef struct		s_data
{
	void			*mlx_ptr;
	void			*mlx_win;
	t_args			*arg;
	float			res_w;
	float			res_h;
	char			*text_n;
	char			*text_s;
	char			*text_e;
	char			*text_w;
	char			*text_spr;
	int				check_space;
	unsigned int	color_ceil;
	int				color_floor;
	t_player		player;
	t_map			*map;
	t_image			image;
	t_lstspr		*lst_spr;
}					t_data;

typedef struct		s_wall
{
	t_intersect		pnt;
	float			width;
	float			height;
	char			card;
}					t_wall;

float				normalise_angle_ret(float angle);
void				normalise_angle(float *angle);
void				init_player(t_data *data, t_player *player, t_map *map);
int					deal_key(int key, t_data *data);
int					deal_close(t_data *data);
void				check_texture(t_data *data);

/*
**	Calcul des distances et des variables
*/

t_intersect			find_first_horizontal_pnt(t_data *data);
t_intersect			find_first_vertical_pnt(t_data *data);
t_wall				ray_length_to_wall(t_data *data);
int					is_angle_x_neg(t_player player);
int					is_angle_y_neg(t_player player);
int					check_wall(t_data *data, t_intersect pnt);
int					count_args(t_data *data, char *str);
void				check_sprite(t_data *data, t_intersect pnt);
void				add_sprites(t_data *data, t_intersect pnt, int x, int y);
t_map				read_map(t_data *data, t_list *list);
int					check_content_map(t_map *m, t_data *data);
void				check_key(t_data *data, char *str);
void				draw_sprite(t_data *data, t_image image, int colonne);
int					draw_wall(t_data *data);
int					wall_limit(int key, t_data *data, float x_mov, float y_mov);
void				black_screen(t_data *data);
int					open_file(t_data *data, char *path_file);
void				take_resolution(t_data *data, char *cont, int i);
int					take_texture1(t_data *data, char *cont, int i);
int					take_data(t_data *data, t_list *list);
int					m_error(char *str, t_data *data, int step);
void				destroy_data(t_data *data, int step);
void				destroy_sprites(t_lstspr **lst);
void				ft_sprclear(t_lstspr **lst);
void				screen_command(t_data *data);
void				screen_bmp(t_data *data);
int					screenshot_bmp(t_data *data);
void				check_cub(t_data *data, char *str);

#endif
