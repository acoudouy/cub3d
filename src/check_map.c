/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoudouy <acoudouy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 13:14:12 by acoudouy          #+#    #+#             */
/*   Updated: 2020/02/14 13:23:38 by acoudouy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_cub3d.h"

static int		check_wall_map(t_data *data, t_map *m)
{
	int		x;
	int		y;

	x = -1;
	y = -1;
	while (++x < m->width)
		if (m->val[0][x] != 1 + '0' || m->val[m->height - 1][x] != 1 + '0')
			return (m_error("Murs non complet", data, 4));
	while (++y < m->height)
		if (m->val[y][0] != 1 + '0' || m->val[y][m->width - 1] != 1 + '0')
			return (m_error("Murs non complet", data, 4));
	return (0);
}

static int		check_char_map(int x, int y, char c, t_data *data)
{
	if (c == '0' || c == '1' || c == '2')
		;
	else if ((c == 'N' || c == 'S' || c == 'E' || c == 'W')
				&& data->map->check_pos == 0)
	{
		data->map->orient_start = c;
		data->map->x_start = x;
		data->map->y_start = y;
		data->map->check_pos++;
	}
	else
		return (m_error("Valeurs de la map invalides", data, 0));
	return (0);
}

int				check_content_map(t_map *m, t_data *data)
{
	int		x;
	int		y;
	char	c;

	x = 0;
	y = 0;
	c = 0;
	while (y < m->height)
	{
		x = 0;
		while (x < m->width)
		{
			c = m->val[y][x];
			if (check_char_map(x, y, c, data) == -1)
				return (-1);
			x++;
		}
		y++;
	}
	if (m->check_pos != 1)
		return (m_error("Pas de position donnee", data, 4));
	if (check_wall_map(data, m) == -1)
		return (-1);
	return (0);
}
