/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguengo <hguengo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 08:48:14 by hguengo           #+#    #+#             */
/*   Updated: 2024/10/18 12:23:20 by hguengo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	join_threads(pthread_t *threads, pthread_t monitor_thread, int n_philo)
{
	int	i;

	i = 0;
	while (i < n_philo)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	pthread_join(monitor_thread, NULL);
}

void	cleanup(t_arg *arg)
{
	int	i;

	i = 0;
	while (i < arg->num_philosophers)
	{
		pthread_mutex_destroy(&arg->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&arg->last_to_eat_mutex);
}

void	create_filosof(int to_die, int to_eat, int to_sleep, t_arg *arg)
{
	int	i;

	i = 0;
	while (i < arg->num_philosophers)
	{
		arg->philosophers[i].id = i + 1;
		arg->philosophers[i].full = 0;
		arg->philosophers[i].left_fork = &arg->forks[i];
		arg->philosophers[i].right_fork = &arg->forks[
			(i + 1) % arg->num_philosophers];
		arg->philosophers[i].time_to_die = to_die;
		arg->philosophers[i].time_to_eat = to_eat;
		arg->philosophers[i].time_to_sleep = to_sleep;
		arg->philosophers[i].last_to_eat = get_current_time();
		arg->philosophers[i].meals = 0;
		arg->philosophers[i].arg = arg;
		pthread_create(&arg->threads[i], NULL, philo_life,
			&arg->philosophers[i]);
		i++;
	}
}

int	is_negative(char *str)
{
	int	i;
	int	signal;

	signal = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '-')
		{
			printf("Error\n");
			signal = 1;
			break ;
		}
		i++;
	}
	return (signal);
}

int	validate_args(int argc, char *argv[])
{
	int	cont;

	cont = 0;
	while (argv[cont])
	{
		if (is_negative(argv[cont]) == 1)
			return (0);
		cont++;
	}
	if (argc < 5 || argc > 6)
	{
		printf("Usage: %s <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> max_meals\n", argv[0]);
		return (1);
	}
	return (-1);
}

pthread_mutex_t* initialize_forks(int num_philosophers)
{
	int		i;

	i = 0;
    pthread_mutex_t *forks = malloc(num_philosophers * sizeof(pthread_mutex_t));
    while (i < num_philosophers)
	{
        pthread_mutex_init(&forks[i], NULL);
		i++;
    }
    return (forks);
}

int main(int argc, char *argv[])
{
    if (validate_args(argc, argv) != -1) return 1;

    pthread_mutex_t *forks;
    pthread_t threads[ft_atoi(argv[1])];
    t_philosopher philosophers[ft_atoi(argv[1])];
    t_arg arg;
    pthread_t monitor_thread;

    if (argc == 6)
		arg.max_meals = ft_atoi(argv[5]);
    else
		arg.max_meals = -1;
    if (ft_atoi(argv[1]) > 200)
		return 0;
    forks = initialize_forks(ft_atoi(argv[1]));
    arg.forks = forks;
    arg.is_dead = 0;
    arg.num_philosophers = ft_atoi(argv[1]);
    arg.philosophers = philosophers;
    arg.threads = threads;
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
