/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_player.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoudouy <acoudouy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 13:33:25 by acoudouy          #+#    #+#             */
/*   Updated: 2019/12/17 18:46:16 by acoudouy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_cub3d.h"

static int		border_lim(int signe, t_data *data, float X_mov, float Y_mov)
{
	if (data->player.X + signe * X_mov <= sz_wall ||
		data->player.X + signe * X_mov >= (data->map->width - 1) * sz_wall)
		return (1);
	if (data->player.Y + signe * Y_mov <= sz_wall ||
		data->player.Y + signe * Y_mov >= (data->map->height - 1) * sz_wall)
		return (1);
	return (0);
}

/// il manque les mouvements sur les cotes avec A D 

int				wall_limit(int key, t_data *data, float X_mov, float Y_mov)
{
	int		signe;
	t_wall	wall;

	signe = 1;
	if (key == K_DOWN)
		signe = -1;
	if (border_lim(signe, data, X_mov, Y_mov) == 1)
		return (1);
	data->player.angle = data->player.front;
	wall = ray_length_to_wall(data);
	if (data->player.X < wall.pnt.X)
	{
		if (data->player.X + signe * X_mov >= wall.pnt.X)
		{
			if (data->player.Y <= wall.pnt.Y)
			{
				if (data->player.Y + signe * Y_mov >= wall.pnt.Y) //
					return (1);
			}
			else if (data->player.Y + signe * Y_mov < wall.pnt.Y)
					return (1);
		}
	}
	else
	{
		if (data->player.X + signe * X_mov < wall.pnt.X)
		{
			if (data->player.Y <= wall.pnt.Y)
			{
				if (data->player.Y + signe * Y_mov >= wall.pnt.Y)
					return (1);
			}
			else if (data->player.Y + signe * Y_mov < wall.pnt.Y)
					return (1);
		}
	}
	return (0);
}

static void		movement_player(int key, t_player *player, t_data *data)
{
	float	X_mov;
	float	Y_mov;

	X_mov = cos(player->front * cv_rad) * player->speed;
	Y_mov = -sin(player->front * cv_rad) * player->speed;
	if (key == K_UP && wall_limit(key, data, X_mov, Y_mov) == 0)
	{
		player->X += X_mov;
		player->Y += Y_mov;
	}
	if (key == K_DOWN && wall_limit(key, data, X_mov, Y_mov) == 0)
	{
		player->X -= X_mov;
		player->Y -= Y_mov;
	}
	if (key == K_LEFT)
		player->front -= rotation;
	if (key == K_RIGHT)
		player->front += rotation;
	if (player->front < 0)
		player->front += 360;
	if (player->front >= 360)
		player->front -= 360;
	player->angle = player->front - view / 2;
}

float				normalise_angle_ret(float angle)
{
	if (angle < 0)
		angle += 360;
	else if (angle >= 360)
		angle -= 360;
	return (angle);
}


int					deal_key(int key, t_data *data)
{
	movement_player(key, &(data->player), data);
	draw_wall(data);
	printf("PLAYER: play.X = %.1f, play.Y = %.1f, front = %.1f\n\n", data->player.X, data->player.Y, data->player.front);
return (0);
}
