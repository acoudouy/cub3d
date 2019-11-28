/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoudouy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 14:36:18 by acoudouy          #+#    #+#             */
/*   Updated: 2019/11/05 09:47:55 by acoudouy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*temp;
	int				i;

	i = 0;
	temp = (unsigned char*)b;
	while (len > 0)
	{
		temp[i] = (unsigned char)c;
		i++;
		len--;
	}
	return (b);
}
