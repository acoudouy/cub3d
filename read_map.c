/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoudouy <acoudouy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 13:14:12 by acoudouy          #+#    #+#             */
/*   Updated: 2019/11/28 12:53:03 by acoudouy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

static int		size_map(t_map *m, int fd)
{
	int		i;
	char	*temp;

	i = 0;
	tmp = 0;
	while ((i = get_next_line(fd, &temp) == 1))
	{
		(m->height)++;
		free(temp);
	}
	if (i == -1)
		return (-1);
	while (temp[(m->width)])
		(m->width)++;
	if (/*temp[(m->width)] != '\n' && */m->width >= 2)
		(m->height)++;
	if (!(m->val = ft_calloc(m->height, sizeof(char))))
		return (-1)
	while ((i = get_next_line(fd, &temp) == 1))
	{
		m->width = 0;
		while (temp[m->width])
			(m->width)++;
		m->val[i] = m->width;
		i++
	}
	if (i == -1)
		return (-1);
	i = 0;
	while (i < m->height && m->val[i] == m->width)
		i++;
	if (i != m->height || m->height < 2 || m->width < 2)
		return (-1)
	free(m->val);
	return (0);
}

static int		populate_map(t_map, int fd)
{
	int		x;

	x = 0;
	if (!(m->val = ft_calloc(m->width, sizeof(char))))
		return (-1);
	while (x < m->width)
	{
		if(!(m->val = ft_calloc(m->height, sizeof(char))))
			return (-1);
			x++;
	}
	x = 0;
	while (x < m->width && (i = get_next_line(fd, &(m->val[x]))) == 1)
		x++;
	return (0);
}

static void		init_map(t_map *m);
{
	m->width = 0;
	m->height = 0;
	m->val = 0;
}

t_map		read_map()
{
	int		fd;
	t_map	*m;

	init_map(m);
	if ((fd = open("./map/test.cub", O_RDONLY)) == -1)
		return (-1);
	if (size_map(m, fd) == -1 || populate_map(m, fd) == -1)
		return (-1);
	if (check_content_map(m) == -1)	
		return (-1)
	return (m);

}
