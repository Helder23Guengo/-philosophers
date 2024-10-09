/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguengo <hguengo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 08:48:14 by hguengo           #+#    #+#             */
/*   Updated: 2024/10/09 12:24:15 by hguengo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc, char *argv[])
{
	pthread_mutex_t *forks;
    if (argc < 5 || argc > 6)
    {
        printf("Usage: %s <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> max_meals\n", argv[0]);
        return 1;
    }

    int num_philosophers = ft_atoi(argv[1]);
    int time_to_die = ft_atoi(argv[2]);
    int time_to_eat = ft_atoi(argv[3]);
    int time_to_sleep = ft_atoi(argv[4]);
    int max_meals = -1;
    
    if(argc == 6)
        max_meals = ft_atoi(argv[5]);
    if(num_philosophers > 200)
        return(0);
    
    pthread_t threads[num_philosophers];
    t_philosopher philosophers[num_philosophers];
    forks = malloc(num_philosophers * sizeof(pthread_mutex_t));
    t_arg	arg;
    arg.max_meals = max_meals;
    pthread_mutex_init(&arg.print_mutex, NULL);
    pthread_mutex_init(&arg.dead_mutex, NULL);
    int i;
    i = 0;
    while ( num_philosophers > i) 
    {
        pthread_mutex_init(&forks[i], NULL);
        i++;
    }
    
    i = 0;
    arg.is_dead = 0;
    arg.start_time = get_current_time();
    while (i < num_philosophers)
    {
        philosophers[i].id = i + 1;
        philosophers[i].left_fork = &forks[i];
        philosophers[i].right_fork = &forks[(i + 1) % num_philosophers];
        philosophers[i].time_to_die = time_to_die;
        philosophers[i].time_to_eat = time_to_eat;
        philosophers[i].time_to_sleep = time_to_sleep;

        philosophers[i].last_to_eat = get_current_time();
        philosophers[i].meals = 0;
        philosophers[i].arg = &arg;
        philosophers[i].start_time = 0;
        pthread_create(&threads[i], NULL, philo_life, &philosophers[i]);
        i++;
    }
    i = 0;
    while (i < num_philosophers)
    {
        pthread_join(threads[i], NULL);
        i++;
    }

    while (i < num_philosophers) 
    {
        pthread_mutex_destroy(&forks[i]);
        i++;
    }
    free(forks);
    return 0;
}
