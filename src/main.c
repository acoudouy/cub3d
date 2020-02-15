/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoudouy <acoudouy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 09:48:48 by acoudouy          #+#    #+#             */
/*   Updated: 2020/02/14 14:53:07 by acoudouy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_cub3d.h"

int				deal_close(t_data *data)
{
	(void)data->mlx_ptr;
	destroy_data(data, 10);
	return (0);
}

void			init_player(t_data *data, t_player *player, t_map *map)
{
	check_texture(data);
	player->x = (float)map->x_start * 64 + 32;
	player->y = (float)map->y_start * 64 + 32;
	if (map->orient_start == 'N')
		player->front = 90;
	else if (map->orient_start == 'E')
		player->front = 0;
	else if (map->orient_start == 'W')
		player->front = 180;
	else
		player->front = 270;
	player->angle = player->front - VIEW / 2;
	player->speed = 30;
}

static int		init_data(t_data *data, char *str)
{
	check_cub(data, str);
	if (!(data->map = malloc(sizeof(t_map))))
		return (m_error("Erreur sur le malloc de la map", data, 1));
	if (!(data->arg = malloc(sizeof(t_args))))
		return (m_error("Erreur sur le malloc du check argument", data, 1));
	data->check_space = 1;
	data->arg->r = 0;
	data->arg->c = 0;
	data->arg->f = 0;
	data->arg->ea = 0;
	data->arg->no = 0;
	data->arg->so = 0;
	data->arg->we = 0;
	data->arg->s = 0;
	return (0);
}

static void		res_data(t_data *data)
{
	if (data->res_w > 2560 || data->res_h > 1440)
	{
		data->res_w = 2560;
		data->res_h = 1440;
	}
	if (data->res_w < 200 || data->res_h < 200)
	{
		data->res_w = 200;
		data->res_h = 200;
	}
}

int				main(int ac, char **av)
{
	t_data			data;

	if (ac == 1 || (ac == 3 && ft_strncmp(av[2], "-save", 6) != 0) || ac >= 4)
		return (m_error("Erreur d'argument au lancement", &data, -1));
	if ((data.mlx_ptr = mlx_init()) == NULL)
		return (m_error("Erreur d'initialisation mlx", &data, 0));
	init_data(&data, av[1]);
	open_file(&data, av[1]);
	res_data(&data);
	if (ac == 3 && ft_strncmp(av[2], "-save", 6) == 0)
		screen_command(&data);
	else if (ac == 2)
	{
		if ((data.mlx_win = mlx_new_window(data.mlx_ptr,
			data.res_w, data.res_h, "cub3D")) == NULL)
			return (m_error("Erreur de fenetre mlx", &data, 0));
		init_player(&data, &(data.player), data.map);
		ray_length_to_wall(&data);
		draw_wall(&data);
		mlx_hook(data.mlx_win, 2, 1L << 0, deal_key, &data);
		mlx_hook(data.mlx_win, 17, 1L << 0, deal_close, &data);
		mlx_loop(data.mlx_ptr);
		destroy_data(&data, 10);
	}
	return (EXIT_SUCCESS);
}
