/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_sprite.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoudouy <acoudouy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 13:39:24 by acoudouy          #+#    #+#             */
/*   Updated: 2020/02/14 10:52:31 by acoudouy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_cub3d.h"

static float			dist_sprite(t_data *data, float x, float y)
{
	float a;
	float b;
	float c;
	float r;

	y = -1 * y;
	a = ((data->lst_spr->sprite->pnt_spr.y - (data->player.y))
			/ (data->lst_spr->sprite->pnt_spr.x - data->player.x + 0.01));
	b = -1;
	c = (data->player.y) - a * data->player.x;
	r = cos(data->player.angle * CV_RAD) * sin(data->player.angle * CV_RAD) -
		cos(data->player.angle * CV_RAD) * (y / 64 + data->player.y / 64)
		- (data->player.x / 64 + cos(data->player.angle * CV_RAD) - x / 64) *
		sin(data->player.angle * CV_RAD);
	y = -1 * y;
	if (r > 0)
		return (-1 * (fabs(a * x + b * y + c) / sqrt(a * a + b * b)));
	if (r == 0)
		return (0.001);
	return (fabs(a * x + b * y + c) / sqrt(a * a + b * b));
}

static t_image			texture_sprite(t_data *data)
{
	t_image		img_spr;
	int			*spr_w;
	int			*spr_h;
	int			i;
	float		dist_plan;

	i = 2;
	spr_w = &i;
	spr_h = &i;
	dist_plan = ((data->res_w / 2) / tan((CV_RAD * VIEW) / 2));
	img_spr.ptr = mlx_xpm_file_to_image(data->mlx_ptr, data->text_spr,
	spr_h, spr_w);
	if (img_spr.ptr == NULL)
		m_error("Texture sprite non conforme ou inexistante", data, 1);
	if ((img_spr.data = (int *)mlx_get_data_addr(img_spr.ptr, &img_spr.bpp,
		&img_spr.sz_line, &img_spr.endian)) == NULL)
		return (img_spr);
	img_spr.s_height = *spr_h * (dist_plan / data->lst_spr->sprite->dist_cent);
	img_spr.s_width = *spr_w * (dist_plan / data->lst_spr->sprite->dist_cent);
	img_spr.ratio = (dist_plan / data->lst_spr->sprite->dist_cent);
	img_spr.width = *spr_w;
	img_spr.height = *spr_h;
	return (img_spr);
}

static void				draw_sprite2(t_data *data, t_image image,
			t_image img_spr, int colonne)
{
	int			y;
	float		texpos;
	int			texy;
	int			texx;
	int			up;

	texx = (int)((data->lst_spr->sprite->dist + 0.5) * 64);
	y = 0;
	texpos = 64 / img_spr.s_height;
	while (y < (int)img_spr.s_height && texx < img_spr.width
			&& texx > 0)
	{
		texy = (int)texpos & 63;
		texpos += (64 / img_spr.s_height);
		up = 37 * data->res_h / data->lst_spr->sprite->dist_cent;
		if (img_spr.data[(int)(texx + 64 * texy)] != 0)
		{
			image.data[(int)(colonne + (int)data->res_w * (y +
						data->res_h / 2 - up))] =
						img_spr.data[(int)(texx + 64 * texy)];
		}
		y++;
	}
	mlx_destroy_image(data->mlx_ptr, img_spr.ptr);
}

void					draw_sprite(t_data *data, t_image image, int colonne)
{
	t_image		img_spr;
	t_lstspr	*temp;

	if (data->lst_spr != NULL)
	{
		data->lst_spr->sprite->dist = (dist_sprite(data,
					data->lst_spr->sprite->x_cent,
					data->lst_spr->sprite->y_cent)) / 64;
		img_spr = texture_sprite(data);
		if (img_spr.ptr == NULL)
			m_error("Erreur sur malloc img_spr", data, 7);
		draw_sprite2(data, image, img_spr, colonne);
		while (data->lst_spr != NULL && data->lst_spr->next != NULL)
		{
			temp = data->lst_spr;
			data->lst_spr = data->lst_spr->next;
			free(temp->sprite);
			free(temp);
			draw_sprite(data, image, colonne);
		}
	}
}
