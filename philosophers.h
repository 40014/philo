/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momazouz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 15:36:19 by momazouz          #+#    #+#             */
/*   Updated: 2024/06/06 15:36:34 by momazouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PHILOSOPHERS
# define PHILOSOPHERS

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct philo
{
    int id;
    int last_meal;
    int eating;
    int number_of_meals;
    long    time_to_die;
    long    time_to_eat;
    long    time_to_sleep;
    pthread_t			thread_id;
    pthread_mutex_t *right_fork;
    pthread_mutex_t *left_fork;
    struct s_data   *data;
    
}   t_philosopher;


typedef struct s_data
{
    int n_thread;
    long    time_to_eat;
    long    time_to_die;
    long    time_to_sleep;
    long    number_of_philo;
    long    number_of_limit_meals;
    long    start_time;
    long    philo_dead; // Flag indicating if a philosopher is dead
    pthread_t   *id;
    pthread_mutex_t *forks;
    pthread_mutex_t mutex; // Mutex to protect shared data
    pthread_mutex_t *right_fork;
    pthread_mutex_t *left_fork;
    t_philosopher   *philo; // Pointer to shared data
    
}   t_data;


int ft_check_arg(int argc, char **argv);
int    ft_check_valid_charcter(char **argv);
long	ft_atoi(const char *str);
int	thread(t_data *data);
int    get_time(void);
int philo_is_dead(t_philosopher *philo);
int philo_is_eating(t_philosopher *philo, int i);
void    message(char *str, t_philosopher *philo);
int philo_takes_forks(t_philosopher *philo);
int one_philo(t_data *data);
long    execout_time(long timee);
int print_message(t_data *data, int id, char *str);

#endif