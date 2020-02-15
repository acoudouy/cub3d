/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_intersection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoudouy <acoudouy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 11:18:50 by acoudouy          #+#    #+#             */
/*   Updated: 2020/02/14 10:17:04 by acoudouy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_cub3d.h"

static void			find_first_horizontal_pnt2(t_data *data, t_intersect *pnt,
				float ya, int signe)
{
	if (is_angle_x_neg(data->player) == 0)
		pnt->x = data->player.x + fabs(((data->player.y - pnt->y) /
		tan(CV_RAD * data->player.angle)));
	else
		pnt->x = data->player.x - fabs(((data->player.y - pnt->y) /
		tan(CV_RAD * data->player.angle)));
	while (pnt->x >= SZ_WALL && pnt->x <= ((data->map->width - 1) * SZ_WALL)
		&& pnt->y >= SZ_WALL && pnt->y <= ((data->map->height - 1) * SZ_WALL)
		&& check_wall(data, *pnt) == 0)
	{
		check_sprite(data, *pnt);
		pnt->y += ya;
		pnt->x += signe * (SZ_WALL / tan(CV_RAD * data->player.angle));
	}
	if (pnt->y < SZ_WALL || pnt->y > ((data->map->height) * SZ_WALL) ||
		pnt->x < SZ_WALL || pnt->x > ((data->map->width) * SZ_WALL))
		pnt->dist = 987654321;
	else
		pnt->dist = hypot(data->player.x - pnt->x, data->player.y - pnt->y);
}

t_intersect			find_first_horizontal_pnt(t_data *data)
{
	t_intersect		pnt;
	int				ya;
	int				signe;

	signe = 1;
	ya = SZ_WALL;
	pnt.orient = 'H';
	if (is_angle_y_neg(data->player) == 0)
	{
		ya = -SZ_WALL;
		pnt.y = floor(data->player.y / SZ_WALL) * (SZ_WALL);
	}
	else
	{
		signe = -1;
		pnt.y = floor(data->player.y / SZ_WALL) * SZ_WALL + SZ_WALL;
	}
	find_first_horizontal_pnt2(data, &pnt, ya, signe);
	return (pnt);
}

static void			find_first_vertical_pnt2(t_data *data, t_intersect *pnt,
				float xa, int sg)
{
	if (is_angle_y_neg(data->player) == 0)
		pnt->y = data->player.y - fabs((((data->player.x - pnt->x) *
		tan(CV_RAD * data->player.angle))));
	else
	{
		sg = -1;
		pnt->y = data->player.y + fabs((((data->player.x - pnt->x) *
		tan(CV_RAD * data->player.angle))));
	}
	if (pnt->y < SZ_WALL || pnt->y > ((data->map->height) * SZ_WALL) ||
		pnt->x < SZ_WALL || pnt->x > ((data->map->width) * SZ_WALL))
		pnt->dist = 9987654321;
	else
	{
		while (pnt->y >= SZ_WALL && pnt->y <= ((data->map->height - 1) *
			SZ_WALL) && pnt->x >= SZ_WALL && pnt->x <= ((data->map->width
			- 1) * SZ_WALL) && check_wall(data, *pnt) == 0)
		{
			check_sprite(data, *pnt);
			pnt->x += xa;
			pnt->y -= sg * (SZ_WALL * fabs(tan(CV_RAD * data->player.angle)));
		}
		pnt->dist = hypot(data->player.x - pnt->x, data->player.y - pnt->y);
	}
}

t_intersect			find_first_vertical_pnt(t_data *data)
{
	t_intersect		pnt;
	int				xa;
	int				signe;

	signe = 1;
	xa = SZ_WALL;
	pnt.orient = 'V';
	if (is_angle_x_neg(data->player) == 0)
		pnt.x = floor(data->player.x / SZ_WALL) * SZ_WALL + SZ_WALL;
	else
	{
		pnt.x = floor(data->player.x / SZ_WALL) * SZ_WALL;
		xa = -SZ_WALL;
	}
	find_first_vertical_pnt2(data, &pnt, xa, signe);
	return (pnt);
}
