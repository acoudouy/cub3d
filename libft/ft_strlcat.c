/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoudouy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/01 14:24:00 by acoudouy          #+#    #+#             */
/*   Updated: 2019/11/07 12:00:29 by acoudouy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	unsigned int j;
	unsigned int res;
	unsigned int sizei;

	res = 0;
	j = 0;
	sizei = 0;
	while (dest[sizei] != '\0' && sizei < size)
		sizei++;
	while (src[res] != '\0')
		res++;
	if (size <= sizei)
		return (res + size);
	else
		res = res + sizei;
	while (src[j] != '\0' && sizei + 1 < size)
	{
		dest[sizei] = src[j];
		sizei++;
		j++;
	}
	dest[sizei] = '\0';
	return (res);
}
