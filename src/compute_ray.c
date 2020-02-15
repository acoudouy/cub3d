/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_ray.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoudouy <acoudouy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 10:31:35 by acoudouy          #+#    #+#             */
/*   Updated: 2020/02/14 10:16:54 by acoudouy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_cub3d.h"

static void			find_cardinal(t_data *data, t_wall *wall)
{
	if (wall->pnt.orient == 'H')
	{
		if (wall->pnt.y > data->player.y)
			wall->card = 'N';
		else
			wall->card = 'S';
	}
	else
	{
		if (wall->pnt.x > data->player.x)
			wall->card = 'W';
		else
			wall->card = 'E';
	}
}

t_wall				ray_length_to_wall(t_data *data)
{
	t_intersect		pnt_h;
	t_intersect		pnt_v;
	t_wall			wall;
	float			dist_plan;

	pnt_h = find_first_horizontal_pnt(data);
	pnt_v = find_first_vertical_pnt(data);
	dist_plan = ((data->res_w / 2) / tan((CV_RAD * VIEW) / 2));
	if (pnt_h.dist <= pnt_v.dist)
		wall.pnt = pnt_h;
	else
		wall.pnt = pnt_v;
	find_cardinal(data, &wall);
	wall.pnt.dist *= cos(CV_RAD *
			(normalise_angle_ret(data->player.front - data->player.angle)));
	wall.height = (SZ_WALL / wall.pnt.dist) * dist_plan;
	return (wall);
}
