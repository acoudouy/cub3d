/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_limit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoudouy <acoudouy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 09:30:56 by acoudouy          #+#    #+#             */
/*   Updated: 2020/02/14 10:13:11 by acoudouy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_cub3d.h"

static float	update_angle_movement(t_data *data, int key)
{
	if (key == K_W)
		data->player.angle = data->player.front;
	else if (key == K_S)
		data->player.angle = normalise_angle_ret(data->player.front + 180);
	else if (key == K_A)
		data->player.angle = normalise_angle_ret(data->player.front + 90);
	else if (key == K_D)
		data->player.angle = normalise_angle_ret(data->player.front - 90);
	return (data->player.angle);
}

static int		wall_limit_spr(int key, t_data *data, float x_mov, float y_mov)
{
	int		signe;
	int		x;
	int		y;

	signe = 1;
	if (key == K_S || key == K_A || key == K_D)
		signe = -1;
	x = floor(data->player.x + signe * x_mov) / 64;
	y = floor(data->player.y + signe * y_mov) / 64;
	if (data->map->val[y][x] == '2')
		return (1);
	return (0);
}

static int		wall_limit2(int key, t_data *data, float x_mov, float y_mov)
{
	int		signe;
	t_wall	wall;

	signe = 1;
	if (key == K_S || key == K_A || key == K_D)
		signe = -1;
	wall = ray_length_to_wall(data);
	if (data->player.x >= wall.pnt.x)
	{
		if (data->player.x + signe * x_mov <= wall.pnt.x)
		{
			if (data->player.y <= wall.pnt.y)
			{
				if (data->player.y + signe * y_mov >= wall.pnt.y)
					return (1);
			}
			else if (data->player.y + signe * y_mov < wall.pnt.y)
				return (1);
		}
	}
	if (wall_limit_spr(key, data, x_mov, y_mov) == 1)
		return (1);
	return (0);
}

int				wall_limit(int key, t_data *data, float x_mov, float y_mov)
{
	int		signe;
	t_wall	wall;

	signe = 1;
	if (key == K_S || key == K_A || key == K_D)
		signe = -1;
	data->player.angle = update_angle_movement(data, key);
	wall = ray_length_to_wall(data);
	if (data->player.x < wall.pnt.x)
	{
		if (data->player.x + signe * x_mov >= wall.pnt.x)
		{
			if (data->player.y <= wall.pnt.y)
			{
				if (data->player.y + signe * y_mov >= wall.pnt.y)
					return (1);
			}
			else if (data->player.y + signe * y_mov < wall.pnt.y)
				return (1);
		}
	}
	if (wall_limit2(key, data, x_mov, y_mov) == 1)
		return (1);
	return (0);
}
