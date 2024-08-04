/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momazouz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 16:49:44 by momazouz          #+#    #+#             */
/*   Updated: 2024/06/06 16:49:50 by momazouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_check_lenght_num(char **str)
{
	int		i;
	long	number;

	i = 1;
	while (str[i])
	{
		number = ft_atoi(str[i]);
		if (number == -1 || number == 0)
		{
			printf("Invalid ARGUMENT\n");
			return (1);
		}
		i++;
	}
	return (0);
}

int	ft_check_valid_charcter(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j] != '\0')
		{
			if (!(argv[i][j] >= '0' && argv[i][j] <= '9')
				&& ((argv[i][j] != ' ') && (argv[i][j] != '+')))
			{
				printf("Invalid ARGUMENT CHARACTER\n");
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	ft_check_arg(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		return (1);
	if (ft_check_valid_charcter(argv) == 1)
		return (1);
	if (ft_check_lenght_num(argv) == 1)
		return (1);
	return (0);
}
