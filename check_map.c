/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoudouy <acoudouy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 13:14:12 by acoudouy          #+#    #+#             */
/*   Updated: 2019/11/28 12:50:35 by acoudouy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

static int		check_wall_map(t_map *m)
{
	int		x;
	int		y;

	x = 0;
	y = 0;
	while (x < m->width)
		if (m->val[x][0] != 1 || m->val[x][m->height - 1] != 1) // height -1 ok ? 
			return (-1);
	while (y < m->height)
		if (m->val[0][y] != 1 || m->val[m->width - 1][y] != 1) // width -1 ok ?
			return (-1);
	return (0);
}

int				check_content_map(t_map *m)
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
			c = m->value[y][x];
				if (!(c == '0' || c == '1' || c == '2' ||
					c == 'N' || c == 'S' || c == 'E' || c == 'W'))
					return (-1);
			x++;
		}
		y++;
	}
	if (check_wall_map(m) == -1)
		return (-1);
	return (0)
}
