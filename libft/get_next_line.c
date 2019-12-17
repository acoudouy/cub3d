/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoudouy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 16:26:01 by acoudouy          #+#    #+#             */
/*   Updated: 2019/11/29 10:30:59 by acoudouy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

# ifndef BUFFER_SIZE
# define BUFFER_SIZE 32
# endif

static int	ft_checkerror(int fd, char **cbuf, int *size_line)
{
	*size_line = 0;
	if (fd == -1)
		return (-1);
	if (!(*cbuf) && !(*cbuf = malloc(sizeof(char) * (BUFFER_SIZE + 1))))
	{
		free(cbuf);
		return (-1);
	}
	return (0);
}

static int	ft_checkbackslash(char *cbuf)
{
	int		size_line;

	size_line = 0;
	while (cbuf[size_line] != '\0')
	{
		if (cbuf[size_line] == '\n')
			return (1);
		size_line++;
	}
	return (0);
}

static char	*ft_readline(int fd, char *cbuf)
{
	int		nb_char;
	char	c_toadd[BUFFER_SIZE + 1];
	char	*temp;

	temp = 0;
	nb_char = BUFFER_SIZE;
	while (ft_checkbackslash(cbuf) == 0 && nb_char > 0)
	{
		nb_char = read(fd, &c_toadd, BUFFER_SIZE);
		if (nb_char == -1)
			return (0);
		c_toadd[nb_char] = '\0';
		temp = ft_strjoin(cbuf, c_toadd);
		free(cbuf);
		cbuf = temp;
	}
	return (cbuf);
}

static char	*ft_cbufavance(char *cbuf, int size_line)
{
	int					i;

	i = 0;
	while (cbuf[i + size_line + 1])
	{
		cbuf[i] = cbuf[i + size_line + 1];
		i++;
	}
	cbuf[i] = cbuf[i + size_line + 1];
	return (cbuf);
}

int			get_next_line(int fd, char **line)
{
	int					size_line;
	static char			*cbuf = 0;

	if (ft_checkerror(fd, &cbuf, &size_line) == -1)
	{
		free(cbuf);
		cbuf = 0;
		return (-1);
	}
	if (ft_checkbackslash(cbuf) == 0)
		cbuf = ft_readline(fd, cbuf);
	if (cbuf == 0)
		return (-1);
	while (cbuf[size_line] && cbuf[size_line] != '\n')
		size_line++;
	*line = ft_substr(cbuf, 0, size_line);
	if (ft_checkbackslash(cbuf) == 1)
		cbuf = ft_cbufavance(cbuf, size_line);
	else
	{
		free(cbuf);
		cbuf = 0;
		return (0);
	}
	return (1);
}
