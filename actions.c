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

int droping_forks(t_philosopher *ph, int i)
{
    if (pthread_mutex_unlock(&ph->data->forks[ph->data->philo[i]]))
        return (0);
    if ()
}

int philo_takes_forks(t_philosopher *philo)
{
    if (philo->id % 2 == 0)
        pthread_mutex_lock(philo->right_fork);
    else
        pthread_mutex_lock(philo->left_fork);
    if (philo->id % 2 == 0)
    {
        if (pthread_mutex_lock(philo->left_fork) != 0)
            return (pthread_mutex_unlock(philo->right_fork), 1);
        if (!philo_is_dead(philo))
            message("has taken a fork", philo);
    }
    else
    {
        if (pthread_mutex_lock(philo->right_fork) != 0)
            return (pthread_mutex_unlock(philo->left_fork), 1);
        if (!philo_is_dead(philo))
            message("has taken a fork", philo);
    }
    return (0);
}
int philo_is_eating(t_philosopher *philo, int i)
{
    if (pthread_mutex_lock(&philo->data->philo[i].left_fork) != 0)
        return (0);
    if (print_message(philo, philo->data->philo[i].id, "has taken a fork") == 0)
        return (0);
    if (pthread_mutex_lock(&philo->data->philo[i].right_fork) != 0)
        return (0);
    if (print_message(philo, philo->data->philo[i].id, "has taken a fork") == 0)
        return (0);
    if (print_message(philo, philo->data->philo[i].id, "is eating") == 0)
        return (0);
    philo->data->philo[i].time_to_die = get_time();
    execout_time(philo->data->time_to_eat);
    droping_forks(philo, i);
    
}
// void    philo_is_eating(t_philosopher *philo)
// {
//     message("is eating", philo);
//     pthread_mutex_lock(&philo->data->mutex);
//     philo->last_meal = get_time() - philo->data->start_time;
//     philo->time_to_die = philo->last_meal + philo->data->time_to_die;
// }

int philo_is_dead(t_philosopher *philo)
{
    pthread_mutex_lock(&philo->data->mutex);
    if (philo->data->philo_dead == 1)
    {
        pthread_mutex_unlock(&philo->data->mutex);
        return (1);
    }
    pthread_mutex_unlock(&philo->data->mutex);
    return (0);
}
