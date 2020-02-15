/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoudouy <acoudouy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 14:18:01 by acoudouy          #+#    #+#             */
/*   Updated: 2020/02/14 10:53:21 by acoudouy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_cub3d.h"

static t_image	texture_wall(t_data *data, t_wall *wall)
{
	t_image		img_xpm;
	int			*size;
	int			i;

	i = (int)data->res_w;
	size = &i;
	if (wall->card == 'S')
		img_xpm.ptr = mlx_xpm_file_to_image(data->mlx_ptr, data->text_n,
				size, size);
	else if (wall->card == 'N')
		img_xpm.ptr = mlx_xpm_file_to_image(data->mlx_ptr, data->text_s,
				size, size);
	else if (wall->card == 'E')
		img_xpm.ptr = mlx_xpm_file_to_image(data->mlx_ptr, data->text_w,
				size, size);
	else
		img_xpm.ptr = mlx_xpm_file_to_image(data->mlx_ptr, data->text_e,
				size, size);
	if (img_xpm.ptr == NULL)
		return (img_xpm);
	if ((img_xpm.data = (int *)mlx_get_data_addr(img_xpm.ptr, &img_xpm.bpp,
					&img_xpm.sz_line, &img_xpm.endian)) == NULL)
		return (img_xpm);
	return (img_xpm);
}

static void		draw_wall3(t_data *data, t_wall wall, int colonne,
		int size_ceil)
{
	int		y;
	int		texx;
	int		texy;
	t_image	img_xpm;

	img_xpm = texture_wall(data, &wall);
	if (img_xpm.ptr == NULL)
		m_error("Erreur avec une texture", data, 1);
	y = -1;
	if (wall.card == 'N' || wall.card == 'S')
		texx = (int)wall.pnt.x % 64;
	else
		texx = (int)wall.pnt.y % 64;
	while (++y < (int)wall.height && y < (int)data->res_h)
	{
		texy = (((y + size_ceil - data->res_h / 2 + wall.height / 2)
					* 64) / (wall.height));
		data->image.data[colonne + (int)data->res_w * (y + size_ceil)] =
			img_xpm.data[(int)(texx + 64 * texy)];
	}
	mlx_destroy_image(data->mlx_ptr, img_xpm.ptr);
	y--;
	while (++y < (int)data->res_h)
		data->image.data[colonne + (int)data->res_w * (y + size_ceil)] =
			data->color_floor;
}

static int		draw_wall2(t_data *data, t_wall wall, int colonne)
{
	int		size_ceil;

	size_ceil = 0;
	while (size_ceil < (int)(((data->res_h - wall.height) / 2)))
	{
		data->image.data[colonne + (int)data->res_w * (size_ceil)] =
			data->color_ceil;
		size_ceil++;
	}
	draw_wall3(data, wall, colonne, size_ceil);
	draw_sprite(data, data->image, colonne);
	return (size_ceil);
}

int				draw_wall(t_data *data)
{
	t_image		image;
	t_wall		wall;
	int			colonne;
	int			size_ceil;

	colonne = (int)data->res_w;
	image.ptr = mlx_new_image(data->mlx_ptr, data->res_w, data->res_h);
	if ((image.data = (int *)mlx_get_data_addr(image.ptr, &image.bpp,
					&image.sz_line, &image.endian)) == NULL)
		return (m_error("Erreur sur malloc image data", data, 5));
	black_screen(data);
	normalise_angle(&(data->player.angle));
	data->image = image;
	while (colonne >= 0)
	{
		destroy_sprites(&data->lst_spr);
		wall = ray_length_to_wall(data);
		size_ceil = draw_wall2(data, wall, colonne);
		colonne--;
		data->player.angle += (float)(VIEW / data->res_w);
		normalise_angle(&(data->player.angle));
	}
	mlx_put_image_to_window(data->mlx_ptr, data->mlx_win, image.ptr, 0, 0);
	mlx_destroy_image(data->mlx_ptr, image.ptr);
	return (0);
}
