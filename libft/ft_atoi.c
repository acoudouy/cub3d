/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoudouy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 13:17:22 by acoudouy          #+#    #+#             */
/*   Updated: 2020/02/14 09:54:35 by acoudouy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_atoi(const char *str)
{
	int				signe;
	int				i;
	int				res;

	signe = 0;
	i = 0;
	res = 0;
	while (str[i] == ' ' || str[i] == '\f' || str[i] == '\n' || str[i] == '\r'
			|| str[i] == '\t' || str[i] == '\v')
		i++;
	if (str[i] != '\0' && (str[i] == '-' || str[i] == '+'))
	{
		if (str[i] == '-')
			signe++;
		i++;
	}
	while (str[i] && str[i] > 47 && str[i] < 58)
	{
		res = res * 10 + str[i] - 48;
		i++;
	}
	if (signe % 2 == 1)
		res = -res;
	return (res);
}
