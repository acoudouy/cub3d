/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_player.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoudouy <acoudouy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 13:33:25 by acoudouy          #+#    #+#             */
/*   Updated: 2020/02/14 10:11:32 by acoudouy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_cub3d.h"

static void		rotation_player(int key, t_player *player)
{
	if (key == K_LEFT)
		player->front += ROTATION;
	if (key == K_RIGHT)
		player->front -= ROTATION;
	if (player->front < 0)
		player->front += 360;
	if (player->front >= 360)
		player->front -= 360;
	player->angle = player->front - VIEW / 2;
}

static void		movement_player2(int key, t_player *player, t_data *data)
{
	if (key == K_A && wall_limit(key, data, cos((player->front - 90) * CV_RAD)
		* player->speed, -sin((player->front - 90) * CV_RAD) * player->speed)
		== 0)
	{
		player->x -= cos((player->front - 90) * CV_RAD) * player->speed;
		player->y -= -sin((player->front - 90) * CV_RAD) * player->speed;
	}
	if (key == K_D && wall_limit(key, data, cos((player->front + 90) * CV_RAD)
		* player->speed, -sin((player->front + 90) * CV_RAD) * player->speed)
		== 0)
	{
		player->x -= cos((player->front + 90) * CV_RAD) * player->speed;
		player->y -= -sin((player->front + 90) * CV_RAD) * player->speed;
	}
}

static void		movement_player(int key, t_player *player, t_data *data)
{
	float	x_mov;
	float	y_mov;

	x_mov = cos(player->front * CV_RAD) * player->speed;
	y_mov = -sin(player->front * CV_RAD) * player->speed;
	if (key == K_W && wall_limit(key, data, x_mov, y_mov) == 0)
	{
		player->x += x_mov;
		player->y += y_mov;
	}
	if (key == K_S && wall_limit(key, data, x_mov, y_mov) == 0)
	{
		player->x -= x_mov;
		player->y -= y_mov;
	}
	movement_player2(key, player, data);
	rotation_player(key, player);
}

int				deal_key(int key, t_data *data)
{
	movement_player(key, &(data->player), data);
	draw_wall(data);
	destroy_sprites(&data->lst_spr);
	if (key == K_ESC)
		destroy_data(data, 10);
	return (0);
}
