/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoudouy <acoudouy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 16:45:06 by acoudouy          #+#    #+#             */
/*   Updated: 2020/02/14 12:55:31 by acoudouy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_cub3d.h"

static void	destroy_map(t_data *data, int step)
{
	int		y;

	y = 0;
	if (step >= 4)
	{
		while (data->map->height > 0 && y < data->map->height)
		{
			free(data->map->val[y]);
			y++;
		}
	}
	free(data->map->val);
}

void		destroy_texture_error(t_data *data)
{
	if (data->arg->s > 0)
		free(data->text_spr);
	if (data->arg->no > 0)
		free(data->text_n);
	if (data->arg->so > 0)
		free(data->text_s);
	if (data->arg->ea > 0)
		free(data->text_e);
	if (data->arg->we > 0)
		free(data->text_w);
	free(data->arg);
}

void		destroy_data(t_data *data, int step)
{
	if (step == 1)
		destroy_texture_error(data);
	if (step == 2)
	{
		free(data->map);
		free(data->arg);
	}
	if (step >= 3)
	{
		destroy_map(data, step);
		free(data->map);
		free(data->arg);
	}
	if (step >= 5)
	{
		free(data->text_n);
		free(data->text_s);
		free(data->text_w);
		free(data->text_e);
		if (data->lst_spr != NULL)
			free(data->lst_spr);
	}
	system("leaks cub3D");
	exit(0);
}

void		destroy_sprites(t_lstspr **lst)
{
	t_lstspr	*temp;
	t_lstspr	*temp2;

	temp2 = *lst;
	temp = NULL;
	if (lst == NULL || *lst == NULL)
		return ;
	while (temp2)
	{
		if (temp2->next)
			temp = temp2->next;
		else
			temp = NULL;
		free(temp2->sprite);
		free(temp2);
		temp2 = temp;
	}
	*lst = NULL;
}
