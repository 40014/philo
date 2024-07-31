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

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct argument
{
	int					number_of_philo;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					num_limit_meals;
}						t_argument;

typedef struct philo
{
	int					id;
	int					num_time_ate;
	unsigned long long	last_time_eat;
	pthread_t			thread_id;
	pthread_mutex_t		eat_mutex;
	int					left_fork;
	int					right_fork;
	struct s_data		*data;
}						t_philosopher;

typedef struct s_data
{
	int					n_thread;
	unsigned long long	start_time;
	int					philo_dead;
	t_argument			argument;
	pthread_mutex_t		*forks;
	pthread_mutex_t		mutex;
	pthread_mutex_t		n_thread_mutex;
	pthread_mutex_t		philo_dead_mutex;
	pthread_t			monitor;
	t_philosopher		*philo;
}						t_data;

int						ft_check_arg(int argc, char **argv);
int						ft_check_valid_charcter(char **argv);
long					ft_atoi(const char *str);
int						thread(t_data *data);
int						get_time(void);
int						philo_is_dead(t_data *philo, int *i);
int						philo_is_eating(t_data *philo, int i);
int						philo_is_sleeping(t_data *philo, int i);
int						philo_is_thinking(t_data *philo, int i);
int						one_philo(t_data *data);
int						print_message(t_data *data, int id, char *str);
int						print_message_one_philo(t_data *data, int id,
							char *str);
void					ft_free(t_data *data);
int						get_philo_dead(t_data *data);
int						ft_join(t_data *data);
int						execute_routine(t_data *philo, int i);
int						check_if_eat_all_meals(t_data *data);

#endif