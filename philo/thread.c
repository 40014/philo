/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momazouz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 13:12:57 by momazouz          #+#    #+#             */
/*   Updated: 2024/06/27 13:48:15 by momazouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	checkers_philo_routine(t_data *data, int i)
{
	pthread_mutex_lock(&data->philo_dead_mutex);
	if (data->philo_dead == 1)
	{
		pthread_mutex_unlock(&data->philo_dead_mutex);
		return (1);
	}
	pthread_mutex_unlock(&data->philo_dead_mutex);
	if (execute_routine(data, i) == 0)
		return (1);
	return (0);
}

int	checkers_philo_monitor(t_data *data)
{
	int	i;
	int	meals_eaten;
	int	philo_dead;

	i = 0;
	pthread_mutex_lock(&data->philo[i].eat_mutex);
	meals_eaten = data->philo[i].num_time_ate;
	pthread_mutex_unlock(&data->philo[i].eat_mutex);
	pthread_mutex_lock(&data->philo_dead_mutex);
	philo_dead = data->philo_dead;
	pthread_mutex_unlock(&data->philo_dead_mutex);
	if (data->argument.num_limit_meals <= meals_eaten || philo_dead == 1)
		return (1);
	if (philo_is_dead(data, &i) == 1)
		return (1);
	return (0);
}

void	*routine_philo(void *philo_arguments)
{
	t_data	*philo;
	int		i;

	philo = (t_data *)philo_arguments;
	pthread_mutex_lock(&philo->n_thread_mutex);
	i = philo->n_thread;
	pthread_mutex_unlock(&philo->n_thread_mutex);
	if (philo->argument.num_limit_meals > 0)
	{
		while (philo->argument.num_limit_meals > philo->philo[i].num_time_ate)
		{
			if (checkers_philo_routine(philo, i) == 1)
				break ;
		}
	}
	else
	{
		while (1)
		{
			if (checkers_philo_routine(philo, i) == 1)
				break ;
		}
	}
	return (NULL);
}

void	*chekers(void *argument)
{
	t_data	*philo;
	int		i;

	philo = (t_data *)argument;
	i = 0;
	if (philo->argument.num_limit_meals > 0)
	{
		while (1)
		{
			if (checkers_philo_monitor(philo) == 1)
				break ;
		}
	}
	else
	{
		while (1)
		{
			if (philo_is_dead(philo, &i) == 1)
				break ;
		}
	}
	return (NULL);
}

int	thread(t_data *data)
{
	int	i;

	pthread_mutex_init(&data->n_thread_mutex, NULL);
	data->philo_dead = 0;
	data->start_time = get_time();
	if (pthread_create(&data->monitor, NULL, &chekers, (void *)data) != 0)
		return (0);
	i = 0;
	while (i < data->argument.number_of_philo)
	{
		pthread_mutex_lock(&data->n_thread_mutex);
		data->n_thread = i;
		if (pthread_create(&data->philo[i].thread_id, NULL, &routine_philo,
				(void *)data) != 0)
		{
			pthread_mutex_unlock(&data->n_thread_mutex);
			return (0);
		}
		pthread_mutex_unlock(&data->n_thread_mutex);
		usleep(1000);
		i++;
	}
	if (ft_join(data) == 1)
		return (0);
	return (1);
}
