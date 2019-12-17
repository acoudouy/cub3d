/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoudouy <acoudouy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 12:25:48 by acoudouy          #+#    #+#             */
/*   Updated: 2019/12/16 17:35:48 by acoudouy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_cub3d.h"

int				check_wall(t_data *data, t_intersect pnt)
{
	int x;
	int y;

	x = floor(pnt.X / sz_wall);
	y = floor(pnt.Y / sz_wall);
	if (x <= 0 || y <= 0 || x >= (data->map->width - 1) || y >= data->map->height - 1)
		return (1);
	if (pnt.orient == 'H')
	{
		if (data->map->val[y - 1][x] == '1')
			return (1);
		if (data->map->val[y][x] == '1')
			return (1);
	}
	if (pnt.orient == 'V')
	{
		if (data->map->val[y][x - 1] == '1')
			return (1);
		if (data->map->val[y][x] == '1')
			return (1);
	}
	return (0);
}

int					is_angle_y_neg(t_player player)
{
	if (player.angle > 180 && player.angle < 360)
		return (1);
	return (0);
}

int					is_angle_x_neg(t_player player)
{
	if (player.angle > 90 && player.angle < 270)
		return (1);
	return (0);
}
