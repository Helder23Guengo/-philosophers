/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguengo <hguengo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 09:51:30 by hguengo           #+#    #+#             */
/*   Updated: 2024/10/11 14:33:42 by hguengo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		get_current_last(size_t time)
{
 	return(get_current_time() - time);	
}

int		live(t_philosopher *philo, t_arg *argay)
{
    int     is_dead;
    
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

int		time_to_die(t_philosopher *philo, t_arg *argay)
{   
    long ft_hard_time = get_current_time() - philo->last_to_eat;
    if (ft_hard_time > (philo->time_to_die + 1))
    {
        pthread_mutex_lock(&argay->dead_mutex);
		argay->is_dead = 1;
        pthread_mutex_unlock(&argay->dead_mutex);

        pthread_mutex_lock(&argay->print_mutex);
        printf("\033[1;31m%ld %d morreu\033[0m\n", get_current_last(philo->arg->start_time) - (get_current_last(philo->arg->start_time) - philo->time_to_die), philo->id);
        pthread_mutex_unlock(&argay->print_mutex);

        return (1);
    }
    return (0);
}

int		time_to_eat(t_philosopher *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_status(philo, "has taken a fork");

	pthread_mutex_lock(philo->right_fork);
	print_status(philo, "has taken a fork");

	print_status(philo, "is eating");
	philo->last_to_eat = get_current_time();
	philo->meals++;
	usleep(philo->time_to_eat * 1000);
    
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	return (0);
}

void	*philo_monitor(void *args)
{
    t_arg *arg = (t_arg *)args;
    int cont;

    cont = 0;
    while (1)
    {
        cont = 0;
        while (cont < arg->num_philosophers) {
            if (time_to_die(&(arg->philosophers[cont]), arg))
			{
                return (NULL);
            }
            cont++;
        }
        usleep(1000);
	}
}

void	*philo_life(void *arg)
{
    t_philosopher *philo = (t_philosopher *)arg;
    t_arg *arg_dead = philo->arg;

    while (live(philo, arg_dead))
	{
        if (philo->arg->max_meals == -1 || philo->meals < philo->arg->max_meals)
		{
            if (time_to_die(philo, arg_dead))
                	break ;
            print_status(philo, "está pensando");
            if (time_to_die(philo, arg_dead))
                	break ;
            time_to_eat(philo);
            print_status(philo, "está dormindo");
            if (time_to_die(philo, arg_dead))
                	break ;
            usleep(philo->time_to_sleep * 1000);
        }
		else
            break;
    }
    return (NULL);
}