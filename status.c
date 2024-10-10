/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguengo <hguengo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 12:48:03 by hguengo           #+#    #+#             */
/*   Updated: 2024/10/10 14:10:45 by hguengo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long    get_current_time()
{
    struct timeval tv;
    
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int     print_status(t_philosopher *philo, const char *status)
{
    t_arg *arg_dead = philo->arg;

    pthread_mutex_lock(&arg_dead->dead_mutex);
    while(arg_dead->is_dead == 1)
        break ;
    pthread_mutex_unlock(&arg_dead->dead_mutex);
    pthread_mutex_lock(&arg_dead->print_mutex);
    printf("%ld %d %s\n", get_current_time() - arg_dead->start_time, philo->id, status);
    pthread_mutex_unlock(&arg_dead->print_mutex);
    return 0;
}

