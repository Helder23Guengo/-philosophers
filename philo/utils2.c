/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguengo <hguengo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 13:13:44 by hguengo           #+#    #+#             */
/*   Updated: 2024/10/23 10:45:22 by hguengo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_negative(char *str)
{
	int	i;
	int	signal;

	signal = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (!(str[i] >= '0' && str[i] <= '9') && str[i] != '+')
		{
			printf("Error\n");
			signal = 1;
			break ;
		}
		i++;
	}
	return (signal);
}

int	validate_args(int argc, char *argv[])
{
	int	cont;

	cont = 1;
	while (argv[cont])
	{
		if (is_negative(argv[cont]) == 1)
			return (0);
		cont++;
	}
	if (argc < 5 || argc > 6)
		return (1);
	return (-1);
}

void	cleanup(t_arg *arg)
{
	int	i;

	i = 0;
	while (i < arg->num_philosophers)
	{
		pthread_mutex_destroy(&arg->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&arg->last_to_eat_mutex);
}

void	low_unlock(t_philosopher *philo)
{
	usleep(philo->time_to_eat * 1000);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}
