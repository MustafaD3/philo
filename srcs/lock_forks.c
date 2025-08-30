/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lock_forks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdalkili <mdalkilic344@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 22:16:22 by mdalkili          #+#    #+#             */
/*   Updated: 2025/08/30 19:11:12 by mdalkili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int	lock_even_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->fork[philo->right]);
	if (*philo->stop_flag)
	{
		pthread_mutex_unlock(philo->fork[philo->right]);
		return (1);
	}
	printf("%ld %d has taken fork\n", time_calc(philo),
		philo->id + 1);
	pthread_mutex_lock(philo->fork[philo->left]);
	if (*philo->stop_flag)
	{
		pthread_mutex_unlock(philo->fork[philo->left]);
		pthread_mutex_unlock(philo->fork[philo->right]);
		return (1);
	}
	printf("%ld %d has taken fork\n", time_calc(philo),
		philo->id + 1);
	return (0);
}

static int	lock_odd_forks(t_philo *philo)
{
	usleep(500);
	if (*philo->stop_flag)
		return (1);
	pthread_mutex_lock(philo->fork[philo->left]);
	if (*philo->stop_flag)
	{
		pthread_mutex_unlock(philo->fork[philo->left]);
		return (1);
	}
	printf("%ld %d has taken fork\n", time_calc(philo),
		philo->id + 1);
	pthread_mutex_lock(philo->fork[philo->right]);
	if (*philo->stop_flag)
	{
		pthread_mutex_unlock(philo->fork[philo->right]);
		pthread_mutex_unlock(philo->fork[philo->left]);
		return (1);
	}
	printf("%ld %d has taken fork\n", time_calc(philo),
		philo->id + 1);
	return (0);
}

void	lock_forks(t_philo *philo)
{
	philo->left = philo->id;
	philo->right = (philo->id + 1) % philo->num_philos;
	if (*philo->stop_flag)
		return ;
	if (philo->id % 2 == 0)
		lock_even_forks(philo);
	else
		lock_odd_forks(philo);
}

void	unlock_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->fork[philo->left]);
	pthread_mutex_unlock(philo->fork[philo->right]);
}
