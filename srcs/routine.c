/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdalkili <mdalkilic344@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 22:21:54 by mdalkili          #+#    #+#             */
/*   Updated: 2025/08/27 22:22:35 by mdalkili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

long	time_calc(t_philo *philo)
{
	return (get_current_time() - philo->start_time);
}

static void	single_philo_routine(t_philo *philo)
{
	pthread_mutex_lock(philo->fork[philo->left]);
	printf("%ld 1 has taken a fork\n", time_calc(philo));
	usleep(philo->time_to_die * 1000);
	pthread_mutex_unlock(philo->fork[philo->left]);
}

static void	philo_cycle(t_philo *philo)
{
	lock_forks(philo);
	if (*philo->stop_flag)
	{
		unlock_forks(philo);
		return ;
	}
	philo->last_meal_time = get_current_time();
	printf("%ld %d is eating\n", time_calc(philo), philo->id + 1);
	ft_usleep(philo->time_to_eat, philo);
	if (*philo->stop_flag)
	{
		unlock_forks(philo);
		return ;
	}
	unlock_forks(philo);
	printf("%ld %d is sleeping\n", time_calc(philo), philo->id + 1);
	ft_usleep(philo->time_to_sleep, philo);
	if (*philo->stop_flag)
		return ;
	printf("%ld %d is thinking\n", time_calc(philo), philo->id + 1);
	philo->num_times_to_eat--;
}

void	routine(t_philo *philo)
{
	if (philo->id % 2 == 0)
		ft_usleep(philo->time_to_eat / 10, philo);
	if (philo->num_philos == 1)
	{
		single_philo_routine(philo);
		return ;
	}
	while ((philo->num_times_to_eat != 0 || philo->num_times_to_eat == -1)
		&& !(*philo->stop_flag))
	{
		if (*philo->stop_flag)
			break ;
		philo_cycle(philo);
	}
}

void	start_threads(t_philo **philo, pthread_mutex_t **forks)
{
	pthread_t	monitor_thread;
	long		start_time;

	start_time = get_current_time();
	init_philos(philo, forks, start_time);
	create_philo_threads(philo);
	pthread_create(&monitor_thread, NULL, (void *)monitor_philos, philo);
	pthread_join(monitor_thread, NULL);
	join_philo_threads(philo);
}
