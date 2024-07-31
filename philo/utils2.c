/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momazouz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 00:44:59 by momazouz          #+#    #+#             */
/*   Updated: 2024/07/27 00:45:06 by momazouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_if_eat_all_meals(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < data->argument.number_of_philo
		&& data->argument.num_limit_meals != -1)
	{
		pthread_mutex_lock(&data->philo[i].eat_mutex);
		if (data->philo[i].num_time_ate < data->argument.num_limit_meals)
			j = 1;
		pthread_mutex_unlock(&data->philo[i].eat_mutex);
		i++;
	}
	if (j == 0 && data->argument.num_limit_meals != -1)
	{
		pthread_mutex_lock(&data->philo_dead_mutex);
		data->philo_dead = 1;
		pthread_mutex_unlock(&data->philo_dead_mutex);
		return (1);
	}
	return (0);
}

int	philo_is_sleeping(t_data *philo, int i)
{
	if (print_message(philo, philo->philo[i].id, "is sleeping") == 0)
		return (0);
	usleep(philo->argument.time_to_sleep * 1000);
	pthread_mutex_lock(&philo->philo_dead_mutex);
	if (philo->philo_dead == 1)
	{
		pthread_mutex_unlock(&philo->philo_dead_mutex);
		return (0);
	}
	pthread_mutex_unlock(&philo->philo_dead_mutex);
	return (1);
}

int	philo_is_thinking(t_data *philo, int i)
{
	if (print_message(philo, philo->philo[i].id, "is thinking") == 0)
		return (0);
	if (philo->argument.time_to_eat > philo->argument.time_to_sleep)
		usleep((philo->argument.time_to_eat - philo->argument.time_to_sleep)
			* 1000);
	return (1);
}

int	execute_routine(t_data *philo, int i)
{
	if (philo_is_eating(philo, i) == 0)
		return (0);
	pthread_mutex_lock(&philo->philo_dead_mutex);
	if (philo->philo_dead == 1)
	{
		pthread_mutex_unlock(&philo->philo_dead_mutex);
		return (0);
	}
	pthread_mutex_unlock(&philo->philo_dead_mutex);
	if (philo_is_sleeping(philo, i) == 0)
		return (0);
	pthread_mutex_lock(&philo->philo_dead_mutex);
	if (philo->philo_dead == 1)
	{
		pthread_mutex_unlock(&philo->philo_dead_mutex);
		return (0);
	}
	pthread_mutex_unlock(&philo->philo_dead_mutex);
	if (philo_is_thinking(philo, i) == 0)
		return (0);
	return (1);
}

int	ft_join(t_data *data)
{
	int	i;

	i = 0;
	if (pthread_join(data->monitor, NULL) != 0)
		return (1);
	while (i < data->argument.number_of_philo)
	{
		if (pthread_join(data->philo[i].thread_id, NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}
