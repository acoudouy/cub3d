/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoudouy <acoudouy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 11:10:39 by acoudouy          #+#    #+#             */
/*   Updated: 2020/02/14 10:17:12 by acoudouy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_cub3d.h"

static void				ft_lst_spr_add_front(t_lstspr **alst, t_lstspr *new)
{
	new->next = *alst;
	*alst = new;
}

static int				check_sprite_exist(t_lstspr **lst, int x, int y)
{
	t_lstspr	*temp;

	temp = *lst;
	if (*lst)
	{
		while (temp->next)
		{
			if ((temp->sprite->x_map == x) && (temp->sprite->y_map == y))
				return (1);
			temp = temp->next;
		}
		if ((temp->sprite->x_map == x) && (temp->sprite->y_map == y))
			return (1);
	}
	return (0);
}

static void				find_cardinal_spr(t_data *data, t_sprites *spr)
{
	if (spr->pnt_spr.orient == 'H')
	{
		if (spr->pnt_spr.y > data->player.y)
			spr->card = 'N';
		else
			spr->card = 'S';
	}
	else
	{
		if (spr->pnt_spr.x > data->player.x)
			spr->card = 'W';
		else
			spr->card = 'E';
	}
}

void					sort_sprite(t_data *data, t_lstspr *new)
{
	t_lstspr	*temp;

	temp = data->lst_spr;
	if (data->lst_spr == NULL || new->sprite->dist_cent >
		data->lst_spr->sprite->dist_cent)
		ft_lst_spr_add_front(&data->lst_spr, new);
	else
	{
		while (temp->next && new->sprite->dist_cent <
			temp->next->sprite->dist_cent)
			temp = temp->next;
		if (temp->next)
			new->next = temp->next;
		temp->next = new;
	}
}

void					add_sprites(t_data *data, t_intersect pnt, int x, int y)
{
	t_lstspr	*new_spr_lst;
	float		dist_plan;

	if (check_sprite_exist(&data->lst_spr, x, y) == 0)
	{
		dist_plan = ((data->res_w / 2) / tan((CV_RAD * VIEW) / 2));
		new_spr_lst = malloc(sizeof(t_lstspr));
		new_spr_lst->sprite = malloc(sizeof(t_sprites));
		new_spr_lst->sprite->pnt_spr = pnt;
		new_spr_lst->sprite->pnt_spr.dist = hypot(data->player.x - pnt.x,
			data->player.y - pnt.y);
		new_spr_lst->sprite->x_map = x;
		new_spr_lst->sprite->y_map = y;
		new_spr_lst->sprite->y_cent = y * SZ_WALL + SZ_WALL / 2;
		new_spr_lst->sprite->x_cent = x * SZ_WALL + SZ_WALL / 2;
		new_spr_lst->sprite->dist_cent = hypot(data->player.x -
			new_spr_lst->sprite->x_cent, data->player.y -
			new_spr_lst->sprite->y_cent);
		new_spr_lst->sprite->height = (SZ_WALL / new_spr_lst->sprite->dist_cent)
		* dist_plan;
		find_cardinal_spr(data, new_spr_lst->sprite);
		new_spr_lst->next = 0;
		sort_sprite(data, new_spr_lst);
	}
}
