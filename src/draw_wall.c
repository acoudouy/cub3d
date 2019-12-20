/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoudouy <acoudouy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 14:18:01 by acoudouy          #+#    #+#             */
/*   Updated: 2019/12/17 18:55:03 by acoudouy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_cub3d.h"

 void			black_screen(t_data *data)
{
	t_image		image;
	int			x;
	int			y;

	x = 0;
	y = 0;
	image.sz_line = res_height;
	image.bpp = 32;
	image.endian = 0;
	if ((image.ptr = mlx_new_image(data->mlx_ptr,res_width, res_height))
		== NULL)
		return ;
	image.data = (int *)mlx_get_data_addr(image.ptr,&image.bpp,&image.sz_line, &image.endian);
	while (x < res_width * res_height - 1)
	{
		image.data[x] = 000000000;
		x++;
	}
	mlx_put_image_to_window(data->mlx_ptr, data->mlx_win, image.ptr,0,0);
	mlx_destroy_image(data->mlx_ptr, image.ptr);
}

static void			normalise_angle(float *angle)
{
	if (*angle < 0)
		*angle += 360;
	else if (*angle >= 360)
		*angle -= 360;
}

static int		color_wall(t_wall wall)  ///
{
	if (wall.card == 'N')
		return(100250100);
	if (wall.card == 'E')
		return(05012560);
	if (wall.card == 'W')
		return(000150150);
	else
		return(250000000);
}

t_image			texture_wall(t_data *data, t_wall *wall, t_image *image)
{
	t_image		img_xpm;
	int			*size;
	int			i;
	int			id_texture;

	i = (int)res_width;
	size = &i;
	if (wall->card == 'N')
		img_xpm.ptr = mlx_xpm_file_to_image(data->mlx_ptr, "../texture/north.XPM", size, size);
	else if (wall->card == 'S')
		img_xpm.ptr = mlx_xpm_file_to_image(data->mlx_ptr, "../texture/south.XPM", size, size);
	else if (wall->card == 'W')
		img_xpm.ptr = mlx_xpm_file_to_image(data->mlx_ptr, "../texture/west.XPM", size, size);
	else
		img_xpm.ptr = mlx_xpm_file_to_image(data->mlx_ptr, "../texture/east.XPM", size, size);
	if ((img_xpm.data = (int *)mlx_get_data_addr(img_xpm.ptr, &img_xpm.bpp, &img_xpm.sz_line, &img_xpm.endian)) == NULL)
		return (img_xpm);  /// erreur normalement
/*
	int y = 0;
	while (img_xpm.data[y])
		y++;
	printf("y = %d |", y);
	printf("sz = %d |", img_xpm.sz_line);
*/	return (img_xpm);
}

void			draw_wall(t_data *data)
{
	t_image		image;
	t_image		img_xpm;
	t_wall		wall;
	int			colonne;
	int			y;
	int			z;
	int			size_ceil;
	int			size_text;
	int			color;
	int			color_ceil;
	int			color_floor;

	colonne = 0;
	color_ceil = 015100200;
	color_floor = 200200100;
	image.ptr = mlx_new_image(data->mlx_ptr,res_width, res_height);
	if ((image.data = (int *)mlx_get_data_addr(image.ptr,&image.bpp,&image.sz_line, &image.endian)) == NULL)
		return ;
	black_screen(data);
	normalise_angle(&(data->player.angle));
	while (colonne < (int)res_width)
	{
		wall = ray_length_to_wall(data);
		color = color_wall(wall);   ////
		y = 0;
		z = 0;
		size_ceil = 0;
		img_xpm = texture_wall(data, &wall, &image);
		size_text = img_xpm.sz_line / 4;
		while (size_ceil < (int)(((res_height - wall.height) / 2)))
		{
			image.data[colonne + (int)res_width * (y + size_ceil)] = color_ceil;
			size_ceil++;
		}
		while (y < (int)wall.height && y < (int)res_height)
		{
			image.data[colonne + (int)res_width * (y + size_ceil)] =
			img_xpm.data[(colonne % size_text) + size_text * (z % size_text)];
			y++;
			z++;
		}
		mlx_destroy_image(data->mlx_ptr, img_xpm.ptr);
		while (y < (int)res_height)
		{
			image.data[colonne + (int)res_width * (y + size_ceil)] = color_floor;
			y++;
		}
		colonne++;
		data->player.angle += (float)(view / res_width);
		normalise_angle(&(data->player.angle));
	}
	mlx_put_image_to_window(data->mlx_ptr, data->mlx_win, image.ptr, 0, 0);
	mlx_destroy_image(data->mlx_ptr, image.ptr);

}
