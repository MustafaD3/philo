/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdalkili <mdalkilic344@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 22:19:10 by mdalkili          #+#    #+#             */
/*   Updated: 2025/08/27 22:23:04 by mdalkili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	init_philos(t_philo **philo, pthread_mutex_t **forks, long start_time)
{
	int	i;

	i = 0;
	while (philo[i])
	{
		philo[i]->fork = forks;
		philo[i]->start_time = start_time;
		philo[i]->last_meal_time = start_time;
		i++;
	}
}

void	create_philo_threads(t_philo **philo)
{
	int	i;

	i = 0;
	while (philo[i])
	{
		pthread_create(&philo[i]->thread, NULL, (void *)routine, philo[i]);
		i++;
	}
}

void	join_philo_threads(t_philo **philo)
{
	int	i;

	i = 0;
	while (philo[i])
	{
		pthread_join(philo[i]->thread, NULL);
		i++;
	}
}
