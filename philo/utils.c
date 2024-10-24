/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguengo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 15:22:11 by hguengo           #+#    #+#             */
/*   Updated: 2024/10/17 15:30:41 by hguengo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_current_last(size_t time)
{
	return (get_current_time() - time);
}

int	ft_atoi(const char *str)
{
	int	num;
	int	np;
	int	cont;

	num = 0;
	np = 1;
	cont = 0;
	while (str[cont] == ' ' || str[cont] == '\f' || str[cont] == '\t'
		|| str[cont] == '\r' || str[cont] == '\n' || str[cont] == '\v')
		cont++;
	if (str[cont] == '+' || str[cont] == '-')
	{
		if (str[cont++] == '-')
			np *= -1;
	}
	while (str[cont] >= '0' && str[cont] <= '9')
	{
		num = (num * 10) + (str[cont] - '0');
		cont++;
	}
	return (num * np);
}

int	live(t_arg *argay)
{
	int	is_dead;

	pthread_mutex_lock(&argay->dead_mutex);
	if (argay->is_dead)
	{
		pthread_mutex_unlock(&argay->dead_mutex);
		return (0);
	}
	is_dead = argay->is_dead;
	pthread_mutex_unlock(&argay->dead_mutex);
	if (is_dead)
		return (0);
	return (1);
}

void	*philo_monitor(void *args)
{
	t_arg	*arg;
	int		cont;

	arg = (t_arg *)args;
	cont = 0;
	while (1)
	{
		cont = 0;
		if (is_all_full(arg->philosophers))
		{
			pthread_mutex_lock(&arg->dead_mutex);
			arg->is_dead = 1;
			pthread_mutex_unlock(&arg->dead_mutex);
			return (NULL);
		}
		while (cont < arg->num_philosophers)
		{
			if (time_to_die(&(arg->philosophers[cont]), arg))
			{
				return (NULL);
			}
			cont++;
		}
		usleep(1000);
	}
}
