/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdalkili <mdalkilic344@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 22:21:54 by mdalkili          #+#    #+#             */
/*   Updated: 2025/08/09 04:50:52 by mdalkili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	lock_forks(t_philo *philo)
{
	philo->left = philo->id;
	philo->right = (philo->id + 1) % philo->num_philos;
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->fork[philo->right]);
		printf("Philosopher %d has taken fork %d\n", philo->id, philo->right);
		pthread_mutex_lock(philo->fork[philo->left]);
		printf("Philosopher %d has taken fork %d\n", philo->id, philo->left);
	}
	else
	{
		pthread_mutex_lock(philo->fork[philo->left]);
		printf("Philosopher %d has taken fork %d\n", philo->id, philo->left);
		pthread_mutex_lock(philo->fork[philo->right]);
		printf("Philosopher %d has taken fork %d\n", philo->id, philo->right);
	}
}

static void	unlock_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->fork[philo->left]);
	pthread_mutex_unlock(philo->fork[philo->right]);
}

static void	routine(t_philo *philo)
{
	philo->last_meal_time = get_current_time();
	if (philo->num_philos == 1)
	{
		pthread_mutex_lock(philo->fork[philo->left]);
		printf("Philosopher %d has taken fork %d\n", philo->id, philo->left);
		usleep(philo->time_to_die * 1000);
		pthread_mutex_unlock(philo->fork[philo->left]);
		return ;
	}
	while ((philo->num_times_to_eat != 0 || philo->num_times_to_eat == -1)
		&& !(*philo->stop_flag))
	{
		lock_forks(philo);
		philo->last_meal_time = get_current_time();
		printf("Philosopher %d is eating\n", philo->id);
		usleep(philo->time_to_eat * 1000);
		unlock_forks(philo);
		printf("Philosopher %d is sleeping\n", philo->id);
		usleep(philo->time_to_sleep * 1000);
		printf("Philosopher %d is thinking\n", philo->id);
		philo->num_times_to_eat--;
	}
}

/* static void	*monitor_philos(t_philo **philo)
{
	int	i;
	int	finished;

	while (1)
	{
		i = 0;
		finished = 1;
		while (philo[i])
		{
			if (philo[i]->last_meal_time + philo[i]->time_to_die
				< get_current_time())
			{
				printf("Philosopher %d has died\n", philo[i]->id);
				*philo[i]->stop_flag = 1;
				return (NULL);
			}
			if (philo[i]->num_times_to_eat != 0)
				finished = 0;
			i++;
		}
		if (finished)
		{
			printf("All philosophers have finished eating\n");
			*philo[0]->stop_flag = 1;
			return (NULL);
		}
		usleep(5000);
	}
	return (NULL);
} */

void	start_threads(t_philo **philo, pthread_mutex_t **forks)
{
	pthread_t	monitor_thread;
	int			i;

	i = 0;
	while (philo[i])
	{
		philo[i]->fork = forks;
		pthread_create(&philo[i]->thread, NULL, (void *)routine, philo[i]);
		i++;
	}
	pthread_create(&monitor_thread, NULL, (void *)monitor_philos, philo);
	pthread_join(monitor_thread, NULL);
	i = 0;
	while (philo[i])
	{
		pthread_join(philo[i]->thread, NULL);
		i++;
	}
}
