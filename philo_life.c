/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguengo <hguengo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 09:51:30 by hguengo           #+#    #+#             */
/*   Updated: 2024/09/30 16:42:54 by hguengo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int     time_to_die(t_philosopher *philo, t_arg *argay)
{
    long    current_time_die = get_current_time() - philo->start_time;
    
    long    time_s_last_meal = current_time_die -  philo->last_to_eat;
    
    philo->last_to_eat = current_time_die;
    
    if ( philo->last_to_eat > philo->time_to_die)
    {
        pthread_mutex_lock(&argay->print_mutex);
        
        printf("\033[1;31m[%ld] %d died\033[0m\n", current_time_die, philo->id);
        argay->is_dead = 1;
        pthread_mutex_unlock(&argay->print_mutex);
        return (argay->is_dead);
    }
    return(0);
}

int time_to_eat(t_philosopher *philo)
{
 
        pthread_mutex_lock(philo->left_fork);
        print_status(philo, "has taken a fork");

        pthread_mutex_lock(philo->right_fork);
        print_status(philo, "has taken a fork");

        print_status(philo, "is eating");
        usleep(philo->time_to_eat * 1000);
       
        pthread_mutex_unlock(philo->right_fork);
        pthread_mutex_unlock(philo->left_fork);
    return 0;
}

void *philo_life(void *arg)
{
    t_philosopher *philo = (t_philosopher *)arg;
    philo->start_time = get_current_time();
    t_arg *arg_dead = philo->arg;

    while (arg_dead->is_dead != 1 && (philo->arg->max_meals == -1 || philo->meals < philo->arg->max_meals))
    {
        print_status(philo, "is thinking");
        if(time_to_die(philo, arg_dead) == 1)
            break ;
        time_to_eat(philo);

        //pthread_mutex_unlock(philo->right_fork);
        //print_status(philo, "dropped fork");

        //pthread_mutex_unlock(philo->left_fork);
       // print_status(philo, "dropped fork");

        print_status(philo, "is sleeping");
        usleep(philo->time_to_sleep * 1000);
        usleep(1000);
    }
    return NULL;
}
