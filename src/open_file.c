/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoudouy <acoudouy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 11:39:21 by acoudouy          #+#    #+#             */
/*   Updated: 2020/02/15 13:23:05 by acoudouy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_cub3d.h"

int				open_file(t_data *data, char *path_file)
{
	int		fd;
	int		i;
	int		check;
	char	*temp;
	t_list	*list;

	list = 0;
	temp = 0;
	check = 0;
	if ((fd = open(path_file, O_RDONLY)) < 0)
		return (m_error("Fichier .cub non ouvrable ou inexistant", data, 0));
	while ((i = get_next_line(fd, &temp)) == 1 && ++check > -1)
		ft_lstadd_back(&list, ft_lstnew(temp));
	close(fd);
	if (check == 0)
	{
		free(temp);
		m_error("Fichier non conforme", data, -1);
	}
	free(temp);
	take_data(data, list);
	ft_lstclear(&list, &free);
	return (0);
}

void			take_resolution(t_data *data, char *cont, int i)
{
	i++;
	i = content_space(i, cont);
	data->res_w = 0;
	data->res_h = 0;
	while (cont[i] >= 48 && cont[i] <= 57)
	{
		data->res_w = data->res_w * 10 + (int)cont[i] - 48;
		i++;
	}
	i = content_space(i, cont);
	while (cont[i] >= 48 && cont[i] <= 57)
	{
		data->res_h = data->res_h * 10 + cont[i] - 48;
		i++;
	}
}

void			check_key(t_data *data, char *str)
{
	if ((str[0] == 'F' && str[1] == ' ') ||
		(str[0] == 'C' && str[1] == ' ') ||
		(str[0] == 'R' && str[1] == ' ') ||
		(str[0] == 'W' && str[1] == 'E') ||
		(str[0] == 'S' && str[1] == 'O') ||
		(str[0] == 'N' && str[1] == 'O') ||
		(str[0] == 'E' && str[1] == 'A') ||
		(str[0] == 'S' && str[1] == ' ') ||
		(str[0] == ' ') || str[0] == '1' || str[0] == '\n' || str[0] == '\0')
		return ;
	else
		m_error("Cle inconnue", data, 1);
}

int				count_args(t_data *data, char *str)
{
	check_key(data, str);
	if ((str[0] == 'R' && data->arg->r != 0) ||
		(str[0] == 'C' && data->arg->c != 0) ||
		(str[0] == 'F' && data->arg->f != 0) ||
		(str[0] == 'W' && str[1] == 'E' && data->arg->we != 0) ||
		(str[0] == 'S' && str[1] == 'O' && data->arg->so != 0) ||
		(str[0] == 'N' && str[1] == 'O' && data->arg->no != 0) ||
		(str[0] == 'E' && str[1] == 'A' && data->arg->ea != 0) ||
		(str[0] == 'S' && str[1] == ' ' && data->arg->s != 0))
		m_error("Il y a deux fois le meme argument", data, 1);
	return (0);
}

int				m_error(char *str, t_data *data, int step)
{
	int		i;

	i = 0;
	ft_putstr_fd("Erreur\n", 1);
	ft_putstr_fd(str, 1);
	write(1, "\n", 1);
	destroy_data(data, step);
	return (-1);
}
