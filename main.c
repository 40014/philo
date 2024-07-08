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

int init(t_data *data)
{
    int i;

    i = 0;
    data->philo = malloc(sizeof(t_philosopher) * data->number_of_philo);
    if (data->philo == NULL)
        return (1);
    while (i < data->number_of_philo)
    {
        data->philo[i].id = i + 1;
        data->philo[i].left_fork = &data->forks[i];
        data->philo[i].right_fork = &data->forks[(i + 1) % data->number_of_philo];
        data->philo[i].data = data;
        data->philo[i].time_to_die = data->time_to_die;
        data->philo[i].time_to_eat = data->time_to_eat;
        data->philo[i].time_to_sleep = data->time_to_sleep;
        data->philo[i].last_meal = 0;
        data->philo[i].eating = 0;
        data->philo[i].number_of_meals = 0;
        i++;
    }
    return (0);
}

int ft_init_struct(t_data *philo, char **argv)
{
    int i;

    i = 0;
    philo->number_of_philo = ft_atoi(argv[1]);
    philo->time_to_die = ft_atoi(argv[2]);
    philo->time_to_eat = ft_atoi(argv[3]);
    philo->time_to_sleep = ft_atoi(argv[4]);
    if (argv[5])
        philo->number_of_limit_meals = ft_atoi(argv[5]);
    else
        philo->number_of_limit_meals = 0;
    philo->philo_dead = 0;
    philo->forks = malloc(sizeof(pthread_mutex_t) * philo->number_of_philo);
    if (philo->forks == NULL)
        return (1);
    while (i < philo->number_of_philo)
    {
        if (pthread_mutex_init(&philo->forks[i], NULL) != 0)
            return (1);
        i++;
    }
    pthread_mutex_init(&philo->mutex, NULL);
    init(philo);
    return (0);
}

// int data_int(t_philo *table)
// {
//     int    i;

//     i = 0;
//     table->
// }

int main(int argc, char **argv)
{
    t_data table;

	if (ft_check_arg(argc, argv) == 1)
        return (1);
    if (ft_init_struct(&table, argv) == 1)
        return (1);
    if (table.number_of_philo == 1)
    {
        if (one_philo(&table) == 0)
            return (1);
        return (0);
    }
    thread(&table);

}
