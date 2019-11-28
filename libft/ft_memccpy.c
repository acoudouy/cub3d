/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoudouy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 15:15:07 by acoudouy          #+#    #+#             */
/*   Updated: 2019/11/06 11:40:43 by acoudouy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned int	i;
	unsigned char	*dst2;
	unsigned char	*src2;

	i = 0;
	dst2 = (unsigned char *)dst;
	src2 = (unsigned char *)src;
	while (i < n && src2[i] != (unsigned char)c)
	{
		dst2[i] = src2[i];
		i++;
	}
	if (src2[i] == (unsigned char)c)
	{
		dst2[i] = src2[i];
		return (dst + i + 1);
	}
	else
		return (0);
}
