/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoudouy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 17:58:41 by acoudouy          #+#    #+#             */
/*   Updated: 2019/11/06 12:08:32 by acoudouy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_calloc(size_t count, size_t size)
{
	char	*temp;
	size_t	i;

	i = 0;
	temp = malloc(size * count);
	if (temp == NULL)
		return (NULL);
	while (i < size * count)
	{
		temp[i] = 0;
		i++;
	}
	return ((void *)temp);
}
