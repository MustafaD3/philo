/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdalkili <mdalkilic344@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 04:04:51 by mdalkili          #+#    #+#             */
/*   Updated: 2025/08/27 21:26:19 by mdalkili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	is_die(t_philo *philo)
{
	if (philo->last_meal_time + philo->time_to_die
		< get_current_time())
	{
		printf("%ld %d died\n", get_current_time()
			- philo->start_time, philo->id + 1);
		*philo->stop_flag = 1;
		return (1);
	}
	return (0);
}

void	*monitor_philos(t_philo **philo)
{
	int	i;
	int	finished;

	while (1)
	{
		i = 0;
		finished = 1;
		while (philo[i])
		{
			if (is_die(philo[i]))
				return (NULL);
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
		usleep(1000);
	}
	return (NULL);
}
