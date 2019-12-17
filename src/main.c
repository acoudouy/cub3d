/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoudouy <acoudouy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 09:48:48 by acoudouy          #+#    #+#             */
/*   Updated: 2019/12/17 18:54:20 by acoudouy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_cub3d.h"

static void		init_player(t_player *player)
{
		player->X = pos_X_start;
		player->Y = pos_Y_start;
		player->front = angle_start;
		player->angle = player->front - view / 2;
		player->speed = 30;
}

static int			init_data(t_data *data)
{
	init_player(&(data->player));
	data->res_w = res_width;
	data->res_h = res_height;
	if (!(data->map = malloc(sizeof(t_map))))
		return (-1);
	return (0);
}

int main(void)
{
    t_data			data;

	if ((data.mlx_ptr = mlx_init()) == NULL)
		return (EXIT_FAILURE);
	init_data(&data);
	if ((data.mlx_win =
		mlx_new_window(data.mlx_ptr, data.res_w, data.res_h, "Cub3D")) == NULL)
	return (EXIT_FAILURE);
	*(data.map) = read_map(&data);
	if (data.map->val == 0)
		return (EXIT_FAILURE);
	ray_length_to_wall(&data);
	draw_wall(&data);
	mlx_hook(data.mlx_win, 2, 1L << 0, deal_key, &data);
	mlx_loop(data.mlx_ptr);
	return (EXIT_SUCCESS);
}
