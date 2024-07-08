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

int	execute_routine(t_philosopher *philo, int i)
{
	if (philo_is_eating(philo, i) == 0)
		return (0);
}

void	routine_philo(void *philo_arguments)
{
	t_philosopher	*philo;
	int	i;

	philo = (t_philosopher *)philo_arguments;
	i = philo->data->n_thread;
	// case of one philosopher
	// conditin of number of time should eat philosophers
	while (philo->data->philo_dead == 0)
	{
		if (execute_routine(philo, i) == 0)
			break;
		if (philo_is_dead(philo))
			return (0);
		philo_takes_forks(philo);
		if (philo_is_dead(philo))
		{
			pthread_mutex_unlock(philo->left_fork);
			pthread_mutex_unlock(philo->right_fork);
			return (0);
		}
		//philo_is_eating(philo);
	}
}

int	thread(t_data *data)
{
	int	i;

	i = 0;
	data->start_time = get_time();
	while (i < data->number_of_philo)
	{
		data->n_thread = i;
		if (pthread_create(&data->philo[i].thread_id, NULL, &routine_philo, &data->philo[i]))
			return (1);
		i++;
		usleep(1000);
	}
	i = 0;
	while (i < data->number_of_philo)
	{
		if (pthread_join(data->id[i], NULL))
			return (1);
		i++;
	}
	return (0);
}
