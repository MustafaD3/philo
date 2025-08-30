/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdalkili <mdalkilic344@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 01:03:05 by mdalkili          #+#    #+#             */
/*   Updated: 2025/08/27 22:29:41 by mdalkili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	exit_with_error(char *message)
{
	printf("%s\n", message);
	exit(EXIT_FAILURE);
}

void	free_philos(t_philo **philo)
{
	int	i;

	i = 0;
	if (!philo)
		return ;
	while (philo[i])
	{
		free(philo[i]);
		i++;
	}
	free(philo);
}

void	free_forks(pthread_mutex_t **forks)
{
	int	i;

	i = 0;
	if (!forks)
		return ;
	while (forks[i])
	{
		free(forks[i]);
		i++;
	}
	free(forks);
}

int	main(int argc, char **argv)
{
	t_philo			**philo;
	pthread_mutex_t	**forks;
	int				*stop_flag;

	stop_flag = malloc(sizeof(int));
	*stop_flag = 0;
	if (!check_arguments(argc, argv))
		return (1);
	philo = parse_arguments(argv, stop_flag);
	if (!philo)
		exit_with_error("Error: Failed to parse arguments\n");
	forks = get_forks(argv);
	if (!forks)
		exit_with_error("Error: Failed to create forks\n");
	start_threads(philo, forks);
	free_philos(philo);
	free_forks(forks);
	free(stop_flag);
	return (0);
}
