/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoudouy <acoudouy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 13:14:12 by acoudouy          #+#    #+#             */
/*   Updated: 2019/11/27 13:35:52 by acoudouy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

int			check_content_map_value(char c)
{
	if (c == '0' || c == '1' || c == '2')
		return (0);
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (0);
	return (-1);
}

int			check_content_map(t_map *m)
{
	int		x;
	int		y;

	x = 0;
	y = 0;
	while (y < m->height)
	{
		x = 0;
		while (x < m->width)
		{
			if (check_content_map(m->value[x][y]) == -1)
				return (-1)
			x++;
		}
		y++;
	}
}


