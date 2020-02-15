/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoudouy <acoudouy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 13:25:12 by acoudouy          #+#    #+#             */
/*   Updated: 2020/02/14 13:00:25 by acoudouy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_cub3d.h"

static int				*take_rgb(char *cont, t_data *data, int i)
{
	int *rgb;

	if ((rgb = ft_calloc(3, sizeof(int))) == NULL)
		m_error("Erreur de calloc sur RGB", data, 5);
	while (cont[i] && ft_isdigit(cont[i]) == 1)
	{
		rgb[0] = rgb[0] * 10 + cont[i] - '0';
		i++;
	}
	i++;
	while (cont[i] && ft_isdigit(cont[i]) == 1)
	{
		rgb[1] = rgb[1] * 10 + cont[i] - '0';
		i++;
	}
	i++;
	while (cont[i] && ft_isdigit(cont[i]) == 1)
	{
		rgb[2] = rgb[2] * 10 + cont[i] - '0';
		i++;
	}
	return (rgb);
}

static void				take_floor_color(t_data *data, char *cont, int i)
{
	int *rgb;

	i++;
	i = content_space(i, cont);
	data->color_floor = 0;
	rgb = take_rgb(cont, data, i);
	if (rgb[0] >= 256 || rgb[1] >= 256 || rgb[2] >= 256)
	{
		free(rgb);
		m_error("Couleur rgb non comprise", data, -1);
	}
	data->color_floor = rgb[0] * 256 * 256 + rgb[1] * 256 + rgb[2];
	free(rgb);
}

static void				take_ceil_color(t_data *data, char *cont, int i)
{
	int *rgb;

	i++;
	i = content_space(i, cont);
	data->color_ceil = 0;
	rgb = take_rgb(cont, data, i);
	if (rgb[0] >= 256 || rgb[1] >= 256 || rgb[2] >= 256)
	{
		free(rgb);
		m_error("Couleur rgb non comprise", data, -1);
	}
	data->color_ceil = rgb[0] * 256 * 256 + rgb[1] * 256 + rgb[2];
	free(rgb);
}

static int				check_env(t_data *data, char *cont)
{
	int		i;

	i = 0;
	i = content_space(i, cont);
	check_key(data, cont + i);
	if (cont[i] == 'R' && count_args(data, cont) == 0)
	{
		take_resolution(data, cont, i);
		data->arg->r += 1;
	}
	if (take_texture1(data, cont, i) == -1)
		return (-1);
	if (cont[i] == 'C' && count_args(data, cont) == 0)
	{
		take_ceil_color(data, cont, i);
		data->arg->c += 1;
	}
	if (cont[i] == 'F' && count_args(data, cont) == 0)
	{
		take_floor_color(data, cont, i);
		data->arg->f += 1;
	}
	return (0);
}

int						take_data(t_data *data, t_list *list)
{
	t_list	*temp;

	temp = list;
	while (temp->next != 0)
	{
		while (temp->content == '\0')
			temp = temp->next;
		if (check_env(data, temp->content) == -1)
			return (m_error("Il y a une erreur dans le .cub", data, 3));
		if (check_beginning_map(temp->content) == 1)
		{
			read_map(data, temp);
			break ;
		}
		temp = temp->next;
	}
	return (0);
}
