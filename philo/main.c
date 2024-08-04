/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momazouz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 15:35:09 by momazouz          #+#    #+#             */
/*   Updated: 2024/06/06 15:35:27 by momazouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_free(t_data *data)
{
	free(data->philo);
	free(data->forks);
}

void	ft_fill(t_data *data, int i, int j)
{
	data->philo[i].id = i + 1;
	data->philo[i].num_time_ate = 0;
	data->philo[i].last_time_eat = get_time();
	data->philo[i].left_fork = i;
	data->philo[i].right_fork = j;
}

int	init(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 1;
	data->philo = malloc(sizeof(t_philosopher)
			* (data->argument.number_of_philo));
	if (data->philo == NULL)
		return (1);
	while (j < data->argument.number_of_philo)
	{
		ft_fill(data, i, j);
		if (pthread_mutex_init(&data->philo[i].eat_mutex, NULL) != 0)
			return (1);
		i++;
		j++;
	}
	j = 0;
	ft_fill(data, i, j);
	if (pthread_mutex_init(&data->philo[i].eat_mutex, NULL) != 0)
		return (1);
	return (0);
}

int	ft_init_struct(t_data *philo, char **argv)
{
	int	i;

	philo->argument.number_of_philo = ft_atoi(argv[1]);
	philo->argument.time_to_die = ft_atoi(argv[2]);
	philo->argument.time_to_eat = ft_atoi(argv[3]);
	philo->argument.time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		philo->argument.num_limit_meals = ft_atoi(argv[5]);
	else
		philo->argument.num_limit_meals = -1;
	init(philo);
	philo->forks = malloc(sizeof(pthread_mutex_t)
			* (philo->argument.number_of_philo));
	if (philo->forks == NULL)
		return (1);
	i = 0;
	while (i < philo->argument.number_of_philo)
	{
		if (pthread_mutex_init(&philo->forks[i], NULL) != 0)
			return (1);
		i++;
	}
	if (pthread_mutex_init(&philo->philo_dead_mutex, NULL) != 0)
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	table;

	if (ft_check_arg(argc, argv) == 1)
		return (1);
	if (ft_init_struct(&table, argv) == 1)
		return (1);
	if (table.argument.number_of_philo == 1)
	{
		if (one_philo(&table) == 0)
			return (1);
		return (0);
	}
	thread(&table);
	ft_free(&table);
	return (0);
}
