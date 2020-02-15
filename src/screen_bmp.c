/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen_bmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoudouy <acoudouy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 13:55:09 by acoudouy          #+#    #+#             */
/*   Updated: 2020/02/14 09:43:54 by acoudouy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_cub3d.h"

static void					set_int_in_char(unsigned char *start, int value)
{
	start[0] = (unsigned char)(value);
	start[1] = (unsigned char)(value >> 8);
	start[2] = (unsigned char)(value >> 16);
	start[3] = (unsigned char)(value >> 24);
}

static int					write_bmp_header(int fd, int filesize,
t_data *data)
{
	int				i;
	unsigned char	bmpfileheader[54];

	i = 0;
	while (i < 54)
		bmpfileheader[i++] = (unsigned char)(0);
	bmpfileheader[0] = (unsigned char)('B');
	bmpfileheader[1] = (unsigned char)('M');
	set_int_in_char(bmpfileheader + 2, filesize);
	bmpfileheader[10] = (unsigned char)(54);
	bmpfileheader[14] = (unsigned char)(40);
	set_int_in_char(bmpfileheader + 18, (int)data->res_w);
	set_int_in_char(bmpfileheader + 22, (int)data->res_h);
	bmpfileheader[26] = (unsigned char)(1);
	bmpfileheader[28] = (unsigned char)(24);
	return (!(write(fd, bmpfileheader, 54) < 0));
}

static unsigned char		*get_color(t_data *data, int j, int i)
{
	unsigned char	*rgb;
	int				color;

	rgb = ft_calloc(3, sizeof(char));
	color = data->image.data[j + i * (int)data->res_w];
	rgb[0] = color % 256;
	color /= 256;
	rgb[1] = color % 256;
	color /= 256;
	rgb[2] = color % 256;
	return (rgb);
}

static int					write_bmp_data(int file, t_data *data, int pad)
{
	const unsigned char	zero[3] = {0, 0, 0};
	int					i;
	int					j;
	unsigned char		*rgb;

	i = (int)data->res_h - 1;
	while (i >= 0)
	{
		j = 0;
		while (j < (int)data->res_w)
		{
			rgb = get_color(data, j, i);
			write(file, rgb, 3);
			if (pad > 0 && write(file, &zero, pad) < 0)
				return (0);
			j++;
			free(rgb);
		}
		i--;
	}
	return (1);
}

int							screenshot_bmp(t_data *data)
{
	int			filesize;
	int			file;
	int			pad;

	pad = (4 - ((int)data->res_w * 3) % 4) % 4;
	filesize = 54 + ((4 * (int)data->res_w + pad) * (int)data->res_h);
	if ((file = open("screenshot.bmp", O_WRONLY | O_CREAT, 0666)) < 0)
		return (m_error("Erreur ouverture du bmp", data, 10));
	if (!write_bmp_header(file, filesize, data))
		return (m_error("Erreur ecriture du header bmp", data, 10));
	if (!write_bmp_data(file, data, pad))
		return (m_error("Erreur ecriture data bmp", data, 10));
	close(file);
	destroy_sprites(&data->lst_spr);
	return (1);
}
