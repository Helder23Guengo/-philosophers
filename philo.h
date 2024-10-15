/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguengo <hguengo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 09:35:40 by hguengo           #+#    #+#             */
/*   Updated: 2024/10/15 16:24:34 by hguengo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

typedef struct s_arg t_arg;


typedef struct s_philosopher
{
	int		id;
	long	last_to_eat;
	int		meals;
	int		full;
	pthread_mutex_t *left_fork;
	pthread_mutex_t *right_fork;
	t_arg	*arg;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	char *argv[];
	//long 	start_time;

}t_philosopher;

struct s_arg
{
	int max_meals;
    int is_dead;
    long start_time;
    int num_philosophers; 
    t_philosopher *philosophers; 
    pthread_mutex_t print_mutex;
    pthread_mutex_t dead_mutex;
	pthread_mutex_t last_to_eat_mutex;
	pthread_mutex_t *forks;
	pthread_t *threads;
};

void *philo_life(void *arg);
long get_current_time();
int ft_atoi(const char *str);
void *philo_monitor(void *args);
int is_all_full(t_philosopher *philo);
int print_status(t_philosopher *philo, const char *status);
void monitors(void *arg);
#endif
