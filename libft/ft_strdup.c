/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoudouy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 08:36:56 by acoudouy          #+#    #+#             */
/*   Updated: 2019/11/04 17:56:39 by acoudouy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	int		i;
	int		size;
	char	*src1;

	i = 0;
	size = 0;
	while (src[size])
		size++;
	src1 = malloc(sizeof(char) * (size + 1));
	if (src1 == 0)
	{
		return (0);
	}
	while (i < size)
	{
		src1[i] = src[i];
		i++;
	}
	src1[i] = '\0';
	return (src1);
}
