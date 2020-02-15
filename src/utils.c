/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoudouy <acoudouy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 14:55:36 by acoudouy          #+#    #+#             */
/*   Updated: 2020/02/14 14:47:53 by acoudouy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_cub3d.h"

int					content_space(int i, char *cont)
{
	while (cont[i] == ' ')
		i++;
	return (i);
}

float				normalise_angle_ret(float angle)
{
	if (angle < 0)
		angle += 360;
	else if (angle >= 360)
		angle -= 360;
	return (angle);
}

void				normalise_angle(float *angle)
{
	if (*angle < 0)
		*angle += 360;
	else if (*angle >= 360)
		*angle -= 360;
}

void				black_screen(t_data *data)
{
	t_image		image;
	int			x;
	int			y;

	x = 0;
	y = 0;
	image.sz_line = data->res_h;
	image.bpp = 32;
	image.endian = 0;
	if ((image.ptr = mlx_new_image(data->mlx_ptr, data->res_w, data->res_h))
		== NULL)
		return ;
	image.data = (int *)mlx_get_data_addr(image.ptr,
	&image.bpp, &image.sz_line, &image.endian);
	while (x < data->res_w * data->res_h - 1)
	{
		image.data[x] = 000000000;
		x++;
	}
	mlx_put_image_to_window(data->mlx_ptr, data->mlx_win, image.ptr, 0, 0);
	mlx_destroy_image(data->mlx_ptr, image.ptr);
}

void				check_texture(t_data *data)
{
	t_image		img;
	int			*size;
	int			i;

	i = 0;
	size = &i;
	if ((img.ptr = mlx_xpm_file_to_image(data->mlx_ptr, data->text_n,
		size, size)) == NULL)
		m_error("Adresse texture nord invalide", data, 1);
	if ((img.ptr = mlx_xpm_file_to_image(data->mlx_ptr, data->text_s,
		size, size)) == NULL)
		m_error("Adresse texture sud invalide", data, 1);
	if ((img.ptr = mlx_xpm_file_to_image(data->mlx_ptr, data->text_w,
		size, size)) == NULL)
		m_error("Adresse texture ouest invalide", data, 1);
	if ((img.ptr = mlx_xpm_file_to_image(data->mlx_ptr, data->text_e,
		size, size)) == NULL)
		m_error("Adresse texture est invalide", data, 1);
	if (data->arg->s > 0 && (img.ptr = mlx_xpm_file_to_image(data->mlx_ptr,
		data->text_spr, size, size)) == NULL)
		m_error("Adresse texture sprite invalide", data, 1);
}
