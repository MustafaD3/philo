/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdalkili <mdalkilic344@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 01:03:20 by mdalkili          #+#    #+#             */
/*   Updated: 2025/08/27 22:22:14 by mdalkili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	long			last_meal_time;
	int				num_times_to_eat;
	int				num_philos;
	int				*stop_flag;
	int				left;
	int				right;
	long			start_time;
	pthread_mutex_t	**fork;
}	t_philo;
int				check_arguments(int argc, char **argv);
int				ft_is_number(char *str);
int				ft_atoi(const char *str);
t_philo			**parse_arguments(char **argv, int *stop_flag);
pthread_mutex_t	**get_forks(char **argv);
void			start_threads(t_philo **philo, pthread_mutex_t **forks);
void			*monitor_philos(t_philo **philo);
int				is_die(t_philo *philo);
long			get_current_time(void);
void			ft_usleep(long time_in_ms, t_philo *philo);
void			lock_forks(t_philo *philo);
void			unlock_forks(t_philo *philo);
void			init_philos(t_philo **philo,
					pthread_mutex_t **forks, long start_time);
void			create_philo_threads(t_philo **philo);
void			join_philo_threads(t_philo **philo);
void			routine(t_philo *philo);
long			time_calc(t_philo *philo);
#endif