/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momazouz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 23:55:29 by momazouz          #+#    #+#             */
/*   Updated: 2024/06/27 23:55:53 by momazouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*routin(void *argumenet)
{
	t_data	*data;

	data = (t_data *)argumenet;
	print_message_one_philo(data, 1, "has taken a fork");
	usleep(data->argument.time_to_die * 1000);
	print_message_one_philo(data, 1, "died");
	return (NULL);
}

int	print_message_one_philo(t_data *data, int id, char *str)
{
	long	t0;

	t0 = get_time() - data->start_time;
	pthread_mutex_lock(&data->mutex);
	printf("%ld    %d      %s\n", t0, id, str);
	pthread_mutex_unlock(&data->mutex);
	return (1);
}

int	one_philo(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_init(&data->mutex, NULL);
	data->start_time = get_time();
	if (pthread_create(&data->philo[i].thread_id, NULL, &routin,
			(void *)data) != 0)
		return (0);
	if (pthread_join(data->philo[i].thread_id, NULL) != 0)
		return (0);
	ft_free(data);
	return (1);
}

int	get_time(void)
{
	struct timeval	time_v;

	gettimeofday(&time_v, NULL);
	return ((time_v.tv_sec * 1000) + (time_v.tv_usec / 1000));
}

int	print_message(t_data *data, int id, char *str)
{
	unsigned long long	time;

	time = get_time() - data->start_time;
	pthread_mutex_lock(&data->philo_dead_mutex);
	if (data->philo_dead == 1)
	{
		pthread_mutex_unlock(&data->philo_dead_mutex);
		return (0);
	}
	else
		printf("%-10lld %-3d %s\n", time, id, str);
	pthread_mutex_unlock(&data->philo_dead_mutex);
	return (1);
}
