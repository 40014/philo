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

void    ft_free(t_data *data)
{
    free(data->philo);
    free(data->forks);
}

long  execout_time(long timee)
{
    if (timee > 0)
        return (get_time() - timee);
    return (0);
}

int print_message(t_data *data, int id, char *str)
{
    long    t0;

    t0 = get_time() - data->start_time; //time_to(data->start_time);
    pthread_mutex_lock(&data->mutex);
    if (data->philo_dead == 1)
    {
        pthread_mutex_lock(&data->mutex);
        return (0);
    }
    else
        printf("%ld    %d      %s\n", t0, id, str);
    pthread_mutex_unlock(&data->mutex);
    return (1);
}

int one_philo(t_data *data)
{
    data->start_time = get_time();
    print_message(data, 1, "has taken a fork");
    usleep(data->time_to_die * 1000);
    print_message(data, 1, "died");
    ft_free(data);
    return (1);
}

void    message(char *str, t_philosopher *philo)
{
    if (!philo_is_dead(philo))
    {
        pthread_mutex_lock(&philo->data->mutex);
        printf("%ld %d %s\n", get_time() - philo->data->start_time, philo->id, str);
        pthread_mutex_unlock(&philo->data->mutex);
    }
}

int    get_time(void)
{
    struct timeval  time_v;

    gettimeofday(&time_v, NULL);
    return ((time_v.tv_sec * 1000) + (time_v.tv_usec / 1000));
}