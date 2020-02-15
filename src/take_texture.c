/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoudouy <acoudouy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 13:41:30 by acoudouy          #+#    #+#             */
/*   Updated: 2020/02/14 10:28:50 by acoudouy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_cub3d.h"

static int			take_texture5(t_data *data, char *cont, int i, int j)
{
	int len;

	if (cont[i] == 'E' && cont[i + 1] == 'A' && count_args(data, cont + i) == 0)
	{
		i = i + 2;
		i = content_space(i, cont);
		len = ft_strlen(&(cont[i]));
		if ((data->text_e = malloc(sizeof(char) * len + 1)) == NULL)
			return (m_error("Erreur sur malloc du char * texture", data, 4));
		while (cont[i + j])
		{
			data->text_e[j] = cont[i + j];
			j++;
		}
		data->text_e[j] = '\0';
		data->arg->ea += 1;
	}
	return (0);
}

static int			take_texture4(t_data *data, char *cont, int i, int j)
{
	int len;

	if (cont[i] == 'S' && cont[i + 1] == ' ' && count_args(data, cont + i) == 0)
	{
		i = i + 2;
		i = content_space(i, cont);
		len = ft_strlen(&(cont[i]));
		if ((data->text_spr = malloc(sizeof(char) * len + 1)) == NULL)
			return (m_error("Erreur sur malloc du char * texture", data, 4));
		while (cont[i + j])
		{
			data->text_spr[j] = cont[i + j];
			j++;
		}
		data->text_spr[j] = '\0';
		data->arg->s = 1;
	}
	else
	{
		if (take_texture5(data, cont, i, j) == -1)
			return (-1);
	}
	return (0);
}

static int			take_texture3(t_data *data, char *cont, int i, int j)
{
	int len;

	if (cont[i] == 'W' && cont[i + 1] == 'E' && count_args(data, cont + i) == 0)
	{
		i = i + 2;
		i = content_space(i, cont);
		len = ft_strlen(&(cont[i]));
		if ((data->text_w = malloc(sizeof(char) * len + 1)) == NULL)
			return (m_error("Erreur sur malloc du char * texture", data, 4));
		while (cont[i + j])
		{
			data->text_w[j] = cont[i + j];
			j++;
		}
		data->text_w[j] = '\0';
		data->arg->we += 1;
	}
	else
	{
		if (take_texture4(data, cont, i, j) == -1)
			return (-1);
	}
	return (0);
}

static int			take_texture2(t_data *data, char *cont, int i, int j)
{
	int len;

	if (cont[i] == 'S' && cont[i + 1] == 'O' && count_args(data, cont + i) == 0)
	{
		i = i + 2;
		i = content_space(i, cont);
		len = ft_strlen(&(cont[i]));
		if ((data->text_s = malloc(sizeof(char) * len + 1)) == NULL)
			return (m_error("Erreur sur malloc du char * texture", data, 4));
		while (cont[i + j])
		{
			data->text_s[j] = cont[i + j];
			j++;
		}
		data->text_s[j] = '\0';
		data->arg->so += 1;
	}
	else
	{
		if (take_texture3(data, cont, i, j) == -1)
			return (-1);
	}
	return (0);
}

int					take_texture1(t_data *data, char *cont, int i)
{
	int		j;
	int		len;

	j = 0;
	if (cont[i] == 'N' && cont[i + 1] == 'O' && count_args(data, cont + i) == 0)
	{
		i = i + 2;
		i = content_space(i, cont);
		len = ft_strlen(&(cont[i]));
		if ((data->text_n = malloc(sizeof(char) * len + 1)) == NULL)
			return (m_error("Erreur sur malloc du char * texture", data, 4));
		while (cont[i + j])
		{
			data->text_n[j] = cont[i + j];
			j++;
		}
		data->text_n[j] = '\0';
		data->arg->no += 1;
	}
	else
	{
		if (take_texture2(data, cont, i, j) == -1)
			return (-1);
	}
	return (0);
}
