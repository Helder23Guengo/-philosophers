/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguengo <hguengo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 08:48:14 by hguengo           #+#    #+#             */
/*   Updated: 2024/10/15 16:24:21 by hguengo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void join_threads(pthread_t *threads, pthread_t monitor_thread, int num_philosophers) {
    int i = 0;
    while (i < num_philosophers) {
        pthread_join(threads[i], NULL);
        i++;
    }
    pthread_join(monitor_thread, NULL);
}

void cleanup(t_arg *arg) {
    int i = 0;
    while (i < arg->num_philosophers) {
        pthread_mutex_destroy(&arg->forks[i]);
        i++;
    }
    pthread_mutex_destroy(&arg->last_to_eat_mutex);
}

void    create_filosof(int time_to_die, int time_to_eat, int time_to_sleep, t_arg *arg)
{
    int i;

    i =0;
    while (i < arg->num_philosophers) 
    {
        arg->philosophers[i].id = i + 1;
        arg->philosophers[i].full = 0;
        arg->philosophers[i].left_fork = &arg->forks[i];
        arg->philosophers[i].right_fork = &arg->forks[(i + 1) % arg->num_philosophers];
        arg->philosophers[i].time_to_die = time_to_die;
        arg->philosophers[i].time_to_eat = time_to_eat;
        arg->philosophers[i].time_to_sleep = time_to_sleep;
        arg->philosophers[i].last_to_eat = get_current_time();
        arg->philosophers[i].meals = 0;
        arg->philosophers[i].arg = arg;
        pthread_create(&arg->threads[i], NULL, philo_life, &arg->philosophers[i]);
        i++;
    }
}

int main(int argc, char *argv[])
{
    pthread_mutex_t *forks;
    pthread_t threads[ft_atoi(argv[1])];
    t_philosopher philosophers[ft_atoi(argv[1])];
    t_arg arg;
    pthread_t monitor_thread;
    int i;

    if (argc < 5 || argc > 6) {
        printf("Usage: %s <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> max_meals\n", argv[0]);
        return 1;
    }
    if (argc == 6)
        arg.max_meals = ft_atoi(argv[5]);
    else
        arg.max_meals= -1;
    if (ft_atoi(argv[1]) > 200)
        return 0;
    forks = malloc(ft_atoi(argv[1]) * sizeof(pthread_mutex_t));
     i = 0;
    while (i < ft_atoi(argv[1]))
        pthread_mutex_init(&forks[i++], NULL);
    arg.forks=forks;
    arg.is_dead = 0;
    arg.num_philosophers = ft_atoi(argv[1]); 
    arg.philosophers = philosophers;
    arg.threads=threads;
    pthread_mutex_init(&arg.print_mutex, NULL);
    pthread_mutex_init(&arg.dead_mutex, NULL);
    pthread_mutex_init(&arg.last_to_eat_mutex, NULL);
    arg.start_time = get_current_time();
    create_filosof(ft_atoi(argv[2]), ft_atoi(argv[3]), ft_atoi(argv[4]), &arg);
  	pthread_create(&monitor_thread, NULL, philo_monitor, &arg);
	join_threads(threads, monitor_thread, arg.num_philosophers);
    cleanup(&arg);
    free(forks);
    return 0;
}
