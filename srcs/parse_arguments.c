/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arguments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdalkili <mdalkilic344@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 01:30:03 by mdalkili          #+#    #+#             */
/*   Updated: 2025/08/30 18:55:48 by mdalkili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

long	get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000L) + (tv.tv_usec / 1000));
}

void	ft_usleep(long time_in_ms, t_philo *philo)
{
	long	start;
	long	now;

	start = get_current_time();
	while (!(*philo->stop_flag))
	{
		now = get_current_time();
		if ((now - start) >= time_in_ms)
			break ;
		usleep(500);
	}
}

static void	push_arguments(t_philo *philo, char **argv, int start_time)
{
	philo->num_philos = ft_atoi(argv[1]);
	philo->time_to_die = ft_atoi(argv[2]);
	philo->time_to_eat = ft_atoi(argv[3]);
	philo->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5] != NULL)
		philo->num_times_to_eat = ft_atoi(argv[5]);
	else
		philo->num_times_to_eat = -1;
	philo->left = philo->id;
	philo->right = (philo->id + 1) % philo->num_philos;
	philo->start_time = start_time;
}

t_philo	**parse_arguments(char **argv, int *flag)
{
	t_philo	**philo;
	int		number_of_philos;
	int		i;
	long	start_time;

	start_time = get_current_time();
	i = 0;
	number_of_philos = ft_atoi(argv[1]);
	philo = (t_philo **)malloc(sizeof(t_philo *) * (number_of_philos + 1));
	if (philo == NULL)
		return (NULL);
	while (i < number_of_philos)
	{
		philo[i] = (t_philo *)malloc(sizeof(t_philo));
		if (philo[i] == NULL)
			return (NULL);
		philo[i]->id = i;
		philo[i]->stop_flag = flag;
		push_arguments(philo[i], argv, start_time);
		i++;
	}
	philo[i] = NULL;
	return (philo);
}

pthread_mutex_t	**get_forks(char **argv)
{
	pthread_mutex_t	**forks;
	int				number_of_philos;
	int				i;

	i = 0;
	number_of_philos = ft_atoi(argv[1]);
	forks = (pthread_mutex_t **)malloc(sizeof(pthread_mutex_t *)
			* (number_of_philos + 1));
	while (i < number_of_philos)
	{
		forks[i] = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
		if (forks[i] == NULL)
			return (NULL);
		pthread_mutex_init(forks[i], NULL);
		i++;
	}
	forks[i] = NULL;
	return (forks);
}
