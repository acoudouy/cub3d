/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoudouy <acoudouy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 13:14:12 by acoudouy          #+#    #+#             */
/*   Updated: 2019/12/16 19:28:17 by acoudouy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_cub3d.h"

static int		size_map(t_map *m, int fd)
{
	int		i;
	int		y;
	char	*temp;
	int		*size;

	y = 0;
	i = 0;
	temp = 0;
	size = 0;
	while ((i = get_next_line(fd, &temp) == 1))
	{
		(m->height)++;
		free(temp);
	}
	close(fd);
	if (i == -1)
		return (-1);
	if ((fd = open(path_map, O_RDONLY)) == -1)  ///
		return (-1);
//	if (/*temp[(m->width - 1)] != '\n' &&*/ m->width < 2) // cas a gerer si ligne vide apres
//		(m->height)--; /// attention
	if (!(size = ft_calloc(m->height, sizeof(int))))
		return (-1);
	while ((i = get_next_line(fd, &temp) == 1))
	{
		m->width = 0;
		while (temp[m->width]) //ft_strlen
			(m->width)++;
		size[y] = m->width;
		y++;
	}
	if (i == -1)
		return (-1);
	while (i < m->height && size[i] == m->width)//i=0 dugnlm'en sers comme une var
		i++;
	if (i != m->height || m->height < 2 || m->width < 2)
		return (-1);
	close(fd);
	free(size);
	return (0);
}

static int		populate_map(t_map *m, int fd)
{
	int		y;
	int		i;

	y = -1;
	i = 0;
	if (!(m->val = ft_calloc(m->height, sizeof(char))))
		return (-1);
	while (++y < m->width)
		if(!(m->val[y] = ft_calloc(m->width, sizeof(char))))
			return (-1);
	if ((fd = open(path_map, O_RDONLY)) == -1) ///
		return (-1);
	y = 0;
	while (y < m->height && (i = get_next_line(fd, &(m->val[y]))) == 1)
		y++;
	if (i == -1)
		return (-1);
	close(fd);
	return (0);
}

static void		init_map(t_map *m)
{
	m->width = 0;
	m->height = 0;
	m->val = 0;
}

t_map			read_map(t_data *data)
{
	int		fd;
	t_map	err; //

	init_map(&err); //
	init_map(data->map);
	if ((fd = open(path_map, O_RDONLY)) == -1) ///
		return (err); // "le fichier n'a pas pu etre ouvert"
	if (size_map(data->map, fd) == -1 || populate_map(data->map, fd) == -1)
		return (err); // la carte n'a pas la bonne taille ou erreur de malloc
	if (check_content_map(data->map) == -1)	
		return (err); // la carte a au moins un elt invalide``	
	return (*(data->map));

}
