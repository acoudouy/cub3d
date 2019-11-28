/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoudouy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/01 12:30:20 by acoudouy          #+#    #+#             */
/*   Updated: 2019/11/06 09:32:34 by acoudouy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	unsigned int i;
	unsigned int j;

	i = 0;
	j = 0;
	if (little[i] == '\0')
		return ((char *)big);
	while (big[j] && j < len)
	{
		i = 0;
		if (big[j] == little[0])
		{
			while (little[i] != '\0' && big[i + j] == little[i] && i + j < len)
				i++;
		}
		if (little[i] == '\0')
			return ((char *)&big[j]);
		j++;
	}
	return (0);
}
