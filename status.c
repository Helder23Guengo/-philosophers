/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguengo <hguengo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 12:48:03 by hguengo           #+#    #+#             */
/*   Updated: 2024/09/30 16:42:56 by hguengo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

pthread_mutex_t print_mutex = PTHREAD_MUTEX_INITIALIZER;

long get_current_time()
{
    struct timeval tv;
    
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int print_status(t_philosopher *philo, const char *status)
{
    long current_time = get_current_time() - philo->start_time;
    t_arg *arg_dead = philo->arg;
    
    if (arg_dead->is_dead != 1)
    {

        pthread_mutex_lock(&print_mutex);
        printf("[%ld] %d %s\n", current_time, philo->id, status);
        pthread_mutex_unlock(&print_mutex);
    }
    return 0;
}
