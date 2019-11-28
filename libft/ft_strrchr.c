/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoudouy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 16:14:17 by acoudouy          #+#    #+#             */
/*   Updated: 2019/11/07 12:29:36 by acoudouy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strrchr(const char *s, int c)
{
	int i;
	int pos;

	i = 0;
	pos = -1;
	if (s[0] == '\0' && c == 0)
		return ((char *)s);
	if (s[0] == '\0')
		return (NULL);
	while (s[i])
	{
		if (s[i] == (unsigned char)c)
			pos = i;
		i++;
	}
	if (c == '\0')
		return ((char *)(s + i));
	if (pos == -1)
		return (NULL);
	return ((char *)s + pos);
}
