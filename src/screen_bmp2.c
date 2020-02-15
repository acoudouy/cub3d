/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen_bmp2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoudouy <acoudouy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 10:19:04 by acoudouy          #+#    #+#             */
/*   Updated: 2020/02/14 14:50:15 by acoudouy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_cub3d.h"

void			screen_command(t_data *data)
{
	if ((data->mlx_win = mlx_new_window(data->mlx_ptr,
					data->res_w, data->res_h, "cub3D")) == NULL)
	{
		m_error("Erreur de fenetre mlx", data, 0);
	}
	init_player(data, &(data->player), data->map);
	ray_length_to_wall(data);
	draw_wall(data);
	mlx_hook(data->mlx_win, 2, 1L << 0, deal_key, data);
	mlx_hook(data->mlx_win, 17, 1L << 0, deal_close, data);
	screenshot_bmp(data);
	destroy_data(data, 10);
}
