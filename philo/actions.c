/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momazouz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 12:34:50 by momazouz          #+#    #+#             */
/*   Updated: 2024/06/28 12:36:11 by momazouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	droping_forks(t_data *philo, int i)
{
	if (pthread_mutex_unlock(&philo->forks[philo->philo[i].left_fork]))
		return (0);
	if (pthread_mutex_unlock(&philo->forks[philo->philo[i].right_fork]))
		return (0);
	return (1);
}

int	even_philo(t_data *data, int i)
{
	if (pthread_mutex_lock(&data->forks[data->philo[i].right_fork]) != 0)
		return (0);
	pthread_mutex_lock(&data->philo_dead_mutex);
	if (data->philo_dead == 1)
	{
		pthread_mutex_unlock(&data->philo_dead_mutex);
		pthread_mutex_unlock(&data->forks[data->philo[i].right_fork]);
		return (0);
	}
	pthread_mutex_unlock(&data->philo_dead_mutex);
	if (print_message(data, data->philo[i].id, "has taken a fork") == 0)
		return (0);
	if (pthread_mutex_lock(&data->forks[data->philo[i].left_fork]) != 0)
		return (0);
	pthread_mutex_lock(&data->philo_dead_mutex);
	if (data->philo_dead == 1)
	{
		droping_forks(data, i);
		pthread_mutex_unlock(&data->philo_dead_mutex);
		return (0);
	}
	pthread_mutex_unlock(&data->philo_dead_mutex);
	if (print_message(data, data->philo[i].id, "has taken a fork") == 0)
		return (0);
	return (1);
}

int	odd_philo(t_data *data, int i)
{
	if (pthread_mutex_lock(&data->forks[data->philo[i].left_fork]) != 0)
		return (0);
	pthread_mutex_lock(&data->philo_dead_mutex);
	if (data->philo_dead == 1)
	{
		pthread_mutex_unlock(&data->forks[data->philo[i].left_fork]);
		pthread_mutex_unlock(&data->philo_dead_mutex);
		return (0);
	}
	pthread_mutex_unlock(&data->philo_dead_mutex);
	if (print_message(data, data->philo[i].id, "has taken a fork") == 0)
		return (0);
	if (pthread_mutex_lock(&data->forks[data->philo[i].right_fork]) != 0)
		return (0);
	pthread_mutex_lock(&data->philo_dead_mutex);
	if (data->philo_dead == 1)
	{
		droping_forks(data, i);
		pthread_mutex_unlock(&data->philo_dead_mutex);
		return (0);
	}
	pthread_mutex_unlock(&data->philo_dead_mutex);
	if (print_message(data, data->philo[i].id, "has taken a fork") == 0)
		return (0);
	return (1);
}

int	philo_is_dead(t_data *philo, int *i)
{
	int	time;

	if (*i == philo->argument.number_of_philo)
		*i = 0;
	pthread_mutex_lock(&philo->philo[*i].eat_mutex);
	time = get_time() - philo->philo[*i].last_time_eat;
	printf("time %d\n", time);
	pthread_mutex_unlock(&philo->philo[*i].eat_mutex);
	if (time > philo->argument.time_to_die)
	{
		print_message(philo, philo->philo[*i].id, "died");
		pthread_mutex_lock(&philo->philo_dead_mutex);
		philo->philo_dead = 1;
		pthread_mutex_unlock(&philo->philo_dead_mutex);
		return (1);
	}
	if (check_if_eat_all_meals(philo) == 1)
		return (1);
	(*i)++;
	return (0);
}

int	philo_is_eating(t_data *data, int i)
{
	if (i % 2 == 0)
	{
		if (even_philo(data, i) == 0)
			return (0);
	}
	else
	{
		if (odd_philo(data, i) == 0)
			return (0);
	}
	if (print_message(data, data->philo[i].id, "is eating") == 0)
		return (0);
	pthread_mutex_lock(&data->philo[i].eat_mutex);
	data->philo[i].last_time_eat = get_time();
	data->philo[i].num_time_ate++;
	pthread_mutex_unlock(&data->philo[i].eat_mutex);
	usleep(data->argument.time_to_eat * 1000);
	droping_forks(data, i);
	return (1);
}
