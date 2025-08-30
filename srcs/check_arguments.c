/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arguments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdalkili <mdalkilic344@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 01:05:32 by mdalkili          #+#    #+#             */
/*   Updated: 2025/08/30 19:07:43 by mdalkili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	check_arguments(int argc, char **argv)
{
	if (argc == 5 || argc == 6)
	{
		while (argc > 1)
		{
			argc--;
			if (!ft_is_number(argv[argc]) || ft_atoi(argv[argc]) <= 0)
			{
				printf("Error: Invalid argument\n");
				return (0);
			}
		}
	}
	else
	{
		printf("Error: Invalid number of arguments\n");
		return (0);
	}
	if (argc == 5 && ft_atoi(argv[5]) < 0)
	{
		printf("Error: Invalid number of times to eat\n");
		return (0);
	}
	return (1);
}
