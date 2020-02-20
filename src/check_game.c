/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoudouy <acoudouy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 12:25:48 by acoudouy          #+#    #+#             */
/*   Updated: 2020/02/17 16:16:05 by acoudouy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_cub3d.h"

int					check_wall(t_data *data, t_intersect pnt)
{
	int x;
	int y;

	x = floor(pnt.x / SZ_WALL);
	y = floor(pnt.y / SZ_WALL);
	if (x <= 0 || y <= 0 || x >= (data->map->width - 1) ||
		y >= data->map->height - 1)
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

void				check_sprite(t_data *data, t_intersect pnt)
{
	int x;
	int y;

	x = floor(pnt.x / SZ_WALL);
	y = floor(pnt.y / SZ_WALL);
	if (pnt.orient == 'H')
	{
		if (data->map->val[y - 1][x] == '2')
			add_sprites(data, pnt, x, y - 1);
		if (data->map->val[y][x] == '2')
			add_sprites(data, pnt, x, y);
	}
	if (pnt.orient == 'V')
	{
		if (data->map->val[y][x - 1] == '2')
			add_sprites(data, pnt, x - 1, y);
		if (data->map->val[y][x] == '2')
			add_sprites(data, pnt, x, y);
	}
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

void				check_cub(t_data *data, char *str)
{
	int		i;

	i = 0;
	while (str[i])
		i++;
	if (i < 5)
		m_error("L'argument n'est pas un .cub", data, -1);
	i = i - 4;
	if (ft_strncmp(str + i, ".cub", 5) != 0)
		m_error("L'argument n'est pas un .cub", data, -1);
}
