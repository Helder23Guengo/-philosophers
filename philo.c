/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguengo <hguengo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 08:48:14 by hguengo           #+#    #+#             */
/*   Updated: 2024/10/15 15:12:49 by hguengo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void join_all_threads(pthread_t *threads, pthread_t monitor_thread, int num_philosophers)
{
    int i;

    i = 0;
    while (i < num_philosophers)
    {
        pthread_join(threads[i], NULL);
        i++;
    }
    pthread_join(monitor_thread, NULL);
}


void cleanup(t_arg *arg, pthread_mutex_t *forks, int num_philosophers)
{
    int i;

    i = 0;
    while (i < num_philosophers)
    {
        pthread_mutex_destroy(&forks[i]);
        i++;
    }
    pthread_mutex_destroy(&arg->last_to_eat_mutex);
    pthread_mutex_destroy(&arg->print_mutex);
    pthread_mutex_destroy(&arg->dead_mutex);
    free(forks);
}

void parse_args(int argc, char *argv[], int *num_philosophers, int *time_to_die, int *time_to_eat, int *time_to_sleep, int *max_meals) {
    if (argc < 5 || argc > 6) {
        printf("Usage: %s <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> max_meals\n", argv[0]);
        exit(1);
    }
    *num_philosophers = ft_atoi(argv[1]);
    *time_to_die = ft_atoi(argv[2]);
    *time_to_eat = ft_atoi(argv[3]);
    *time_to_sleep = ft_atoi(argv[4]);
    *max_meals = (argc == 6) ? ft_atoi(argv[5]) : -1;
}

void init_mutexes(pthread_mutex_t *forks, int num_philosophers, t_arg *arg)
{
    int i;
    
    i = 0;
    pthread_mutex_init(&arg->print_mutex, NULL);
    pthread_mutex_init(&arg->dead_mutex, NULL);
    pthread_mutex_init(&arg->last_to_eat_mutex, NULL);
    while (i < num_philosophers)
    {
        pthread_mutex_init(&forks[i], NULL);
        i++;
    }
}

void create_philosophers(t_philosopher *philosophers, pthread_mutex_t *forks, int num_philosophers, int time_to_die, int time_to_eat, int time_to_sleep, t_arg *arg)
{
    int i;

    i = 0;
    while (i < num_philosophers)
    {
        philosophers[i].id = i + 1;
        philosophers[i].full = 0;
        philosophers[i].left_fork = &forks[i];
        philosophers[i].right_fork = &forks[(i + 1) % num_philosophers];
        philosophers[i].time_to_die = time_to_die;
        philosophers[i].time_to_eat = time_to_eat;
        philosophers[i].time_to_sleep = time_to_sleep;
        philosophers[i].last_to_eat = get_current_time();
        philosophers[i].meals = 0;
        philosophers[i].arg = arg;
        i++;
    }
}

void create_threads(pthread_t *threads, t_philosopher *philosophers, int num_philosophers)
{
    int     i;

    i = 0;
    while (i < num_philosophers)
    {
        pthread_create(&threads[i], NULL, philo_life, &philosophers[i]);
        i++;
    }
}

void start_monitor(pthread_t *monitor_thread, t_arg *arg)
{
    pthread_create(monitor_thread, NULL, philo_monitor, arg);
}

int main(int argc, char *argv[])
{
    int num_philosophers, time_to_die, time_to_eat, time_to_sleep, max_meals;
    pthread_mutex_t *forks;
    t_philosopher *philosophers;
    pthread_t *threads, monitor_thread;
    t_arg arg;

    parse_args(argc, argv, &num_philosophers, &time_to_die, &time_to_eat, &time_to_sleep, &max_meals);

    if (num_philosophers > 200)
        return 0;

    forks = malloc(num_philosophers * sizeof(pthread_mutex_t));
    philosophers = malloc(num_philosophers * sizeof(t_philosopher));
    threads = malloc(num_philosophers * sizeof(pthread_t));

    arg.max_meals = max_meals;
    arg.is_dead = 0;
    arg.num_philosophers = num_philosophers;
    arg.philosophers = philosophers;
    arg.start_time = get_current_time();

    init_mutexes(forks, num_philosophers, &arg);
    create_philosophers(philosophers, forks, num_philosophers, time_to_die, time_to_eat, time_to_sleep, &arg);
    create_threads(threads, philosophers, num_philosophers);
    start_monitor(&monitor_thread, &arg);
    join_all_threads(threads, monitor_thread, num_philosophers);
    cleanup(&arg, forks, num_philosophers);

    free(philosophers);
    free(threads);
    return 0;
}
