/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoudouy <acoudouy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 13:14:12 by acoudouy          #+#    #+#             */
/*   Updated: 2020/02/14 13:16:02 by acoudouy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_cub3d.h"

static void		init_map(t_map *m)
{
	m->width = 0;
	m->height = 0;
	m->val = 0;
	m->check_pos = 0;
}

static void		size_map(t_data *data, t_list *list)
{
	int				x;
	int				comp;
	t_list			*temp;

	temp = list;
	if (((char *)(list->content))[1] == ' ')
	{
		data->check_space = 2;
		x = ft_strlen(list->content) / 2 + 1;
	}
	else
		x = ft_strlen(list->content);
	while (temp->next)
	{
		if (data->check_space == 2)
			comp = ft_strlen(temp->content) / 2 + 1;
		else
			comp = ft_strlen(temp->content);
		if (x != comp)
			m_error("Erreur sur la taille de la carte", data, 3);
		temp = temp->next;
	}
	data->map->height = ft_lstsize(list);
	data->map->width = x;
}

static int		populate_map(t_data *data, t_list *list)
{
	int		y;
	int		x;
	t_list	*temp;

	y = 0;
	x = 0;
	temp = list;
	if ((data->map->val = malloc(sizeof(char *) * data->map->height)) == 0)
		return (m_error("Erreur sur le malloc populate map", data, 2));
	while (y < data->map->height)
	{
		if ((data->map->val[y] = malloc(data->map->width + 1)) == 0)
			return (m_error("Erreur sur le malloc populate map", data, 3));
		x = 0;
		while (x < data->map->width)
		{
			data->map->val[y][x] =
			((char *)(temp->content))[x * data->check_space];
			x++;
		}
		data->map->val[y][x] = '\0';
		y++;
		temp = temp->next;
	}
	return (0);
}

t_map			read_map(t_data *data, t_list *list)
{
	init_map(data->map);
	size_map(data, list);
	populate_map(data, list);
	check_content_map(data->map, data);
	return (*(data->map));
}

int				check_beginning_map(char *cont)
{
	if (cont[0] == '1')
		return (1);
	return (0);
}
