/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguengo <hguengo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 09:51:30 by hguengo           #+#    #+#             */
/*   Updated: 2024/10/09 16:35:39 by hguengo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_current_last(size_t time)
{
	t_philosopher *philo;
 	return(get_current_time() - time - philo->time_to_die);	
}

int     time_to_die(t_philosopher *philo, t_arg *argay)
{	
	long ft_hard_time = get_current_time() - philo->last_to_eat;
	if (ft_hard_time > (philo->time_to_die + 1))
	{
     
		pthread_mutex_lock(&argay->dead_mutex);
        if (argay->is_dead)
            return (pthread_mutex_unlock(&argay->dead_mutex), 0);
        pthread_mutex_lock(&argay->print_mutex);
		printf("\033[1;31m%ld %d morreu\033[0m\n",get_current_last(philo->arg->start_time) - ( get_current_last(philo->arg->start_time) - philo->time_to_die), philo->id);
		argay->is_dead = 1;
		pthread_mutex_unlock(&argay->print_mutex);
		return 1;
	}
	return 0;
}

void	live(t_philosopher *philo, t_arg *argay)
{
	pthread_mutex_lock(argay->dead_mutex);
	argay->is_dead = 1;
	pthread_mutex_unlock(argay->dead_mutex);
}

int	time_to_eat(t_philosopher *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_status(philo, "has taken a fork");

	pthread_mutex_lock(philo->right_fork);
	print_status(philo, "has taken a fork");

	print_status(philo, "is eating");
	philo->last_to_eat = get_current_time();
	philo->meals++;
	usleep(philo->time_to_eat * 1000);

	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	
	return 0;
}

void *philo_life(void *arg) {
    t_philosopher *philo = (t_philosopher *)arg;
    t_arg *arg_dead = philo->arg;
    while (philo->arg->max_meals == -1 || philo->meals < philo->arg->max_meals) {
        if(live(philo, arg))
		{
			if (time_to_die(philo, arg_dead))
            break;
      
        print_status(philo, "está pensando");
        if (time_to_die(philo, arg_dead) == 1)
            break;
			
        time_to_eat(philo);
		
        
        print_status(philo, "está dormindo");
        
        if (time_to_die(philo, arg_dead) == 1)
            break;
        usleep(philo->time_to_sleep * 1000);
		}
    }
    return NULL;
}


