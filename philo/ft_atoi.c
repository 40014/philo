/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momazouz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 04:24:27 by momazouz          #+#    #+#             */
/*   Updated: 2024/04/30 04:24:30 by momazouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	ft_atoi(const char *str)
{
	int		i;
	int		n;
	long	r;

	i = 0;
	n = 1;
	r = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] == '+')
		i++;
	while (str[i] >= 48 && str[i] <= 57)
	{
		r = r * 10 + str[i] - '0';
		if (r > 2147483647)
			return (-1);
		i++;
	}
	while (str[i] != '\0')
	{
		if (str[i] != ' ')
			return (-1);
		i++;
	}
	return (r * n);
}
