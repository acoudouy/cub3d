/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_ray.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoudouy <acoudouy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 10:31:35 by acoudouy          #+#    #+#             */
/*   Updated: 2019/12/17 18:54:34 by acoudouy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_cub3d.h"

static t_intersect	find_first_horizontal_pnt(t_data *data)
{
	t_intersect		pnt;
	int				Ya;
	int				signe;

	signe = 1;
	Ya = sz_wall;
	pnt.orient = 'H';
	if (is_angle_y_neg(data->player) == 0)
	{
		Ya = -sz_wall;
		pnt.Y = floor(data->player.Y / sz_wall) * (sz_wall);
	}
	else
	{
		signe = -1;
		pnt.Y = floor(data->player.Y / sz_wall) * sz_wall + sz_wall;
	}
	if (is_angle_x_neg(data->player) == 0)
		pnt.X = data->player.X + fabs(((data->player.Y - pnt.Y) / tan(cv_rad * data->player.angle)));
	else
		pnt.X = data->player.X - fabs(((data->player.Y - pnt.Y) / tan(cv_rad * data->player.angle)));
	while (pnt.X >= sz_wall && pnt.X <= ((data->map->width - 1) * sz_wall)
		&& pnt.Y >= sz_wall && pnt.Y <= ((data->map->height - 1) * sz_wall)
		&& check_wall(data, pnt) == 0)
	{
		pnt.Y += Ya;
		pnt.X += signe * (sz_wall / tan(cv_rad * data->player.angle));
	}
	if (pnt.Y < sz_wall || pnt.Y > ((data->map->height ) * sz_wall) ||
		pnt.X < sz_wall || pnt.X > ((data->map->width) * sz_wall))
		pnt.dist = 987654321;
	else
		pnt.dist = hypot(data->player.X - pnt.X, data->player.Y - pnt.Y);
	return (pnt);
}

static t_intersect find_first_vertical_pnt(t_data *data)
{
	t_intersect		pnt;
	int				Xa;
	int				signe;


	signe = 1;
	Xa = sz_wall;
	pnt.orient = 'V';
	if (is_angle_x_neg(data->player) == 0)
		pnt.X = floor(data->player.X / sz_wall) * sz_wall + sz_wall;
	else
	{
		pnt.X = floor(data->player.X / sz_wall) * sz_wall;
		Xa = -sz_wall;
	}
	if (is_angle_y_neg(data->player) == 0)
		pnt.Y = data->player.Y - fabs((((data->player.X - pnt.X) * tan(cv_rad * data->player.angle))));
	else
	{
		signe = -1;
		pnt.Y = data->player.Y + fabs((((data->player.X - pnt.X) * tan(cv_rad * data->player.angle))));
	}
	if (pnt.Y < sz_wall || pnt.Y > ((data->map->height) * sz_wall) ||
		pnt.X < sz_wall || pnt.X > ((data->map->width) * sz_wall))
		pnt.dist = 987654321;
	else
	{
		while (pnt.Y >= sz_wall && pnt.Y <= ((data->map->height - 1) * sz_wall)
			&& pnt.X >= sz_wall && pnt.X <= ((data->map->width - 1) * sz_wall)
			&& check_wall(data, pnt) == 0)
		{
			pnt.X += Xa;
			pnt.Y -= signe * (sz_wall * fabs(tan(cv_rad * data->player.angle)));
		}
		pnt.dist = hypot(data->player.X - pnt.X, data->player.Y - pnt.Y);
	}
	return (pnt);
}
static void				find_cardinal(t_data *data, t_wall *wall)
{
	if (wall->pnt.orient == 'H')
	{
		if (wall->pnt.Y > data->player.Y)
			wall->card = 'N';
		else
			wall->card = 'S';
	}
	else
	{
		if (wall->pnt.X > data->player.X)
			wall->card = 'W';
		else
			wall->card = 'E';
	}
}

t_wall				ray_length_to_wall(t_data *data)
{
	t_intersect		pnt_H;
	t_intersect		pnt_V;
	t_wall			wall;

	pnt_H = find_first_horizontal_pnt(data);
	pnt_V = find_first_vertical_pnt(data);
	if (pnt_H.dist <= pnt_V.dist)
		wall.pnt = pnt_H;
	else
		wall.pnt = pnt_V;
	find_cardinal(data, &wall);
	wall.pnt.dist *= cos(cv_rad *
			(normalise_angle_ret(data->player.front - data->player.angle)));
	wall.height = (sz_wall / wall.pnt.dist) * dist_plan;
	return (wall);
}
