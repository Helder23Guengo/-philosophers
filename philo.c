/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguengo <hguengo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 08:48:14 by hguengo           #+#    #+#             */
/*   Updated: 2024/10/18 19:04:44 by hguengo          ###   ########.fr       */
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

pthread_mutex_t	*initialize_forks(int num_philosophers)
{
	int				i;
	pthread_mutex_t	*forks;

	forks = malloc(num_philosophers * sizeof(pthread_mutex_t));
	i = 0;
	while (i < num_philosophers)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
	return (forks);
}

int	init_main_aux(int argc, char *argv[], t_main_aux *main_aux)
{
	int	num_philo;

	num_philo = ft_atoi(argv[1]);
	main_aux->threads = malloc(num_philo * sizeof(pthread_t));
	main_aux->philosophers = malloc(num_philo * sizeof(t_philosopher));
	if (argc == 6)
		main_aux->arg.max_meals = ft_atoi(argv[5]);
	else
		main_aux->arg.max_meals = -1;
	if (ft_atoi(argv[1]) > 200)
		return (0);
	main_aux->forks = initialize_forks(ft_atoi(argv[1]));
	main_aux->arg.forks = main_aux->forks;
	main_aux->arg.is_dead = 0;
	main_aux->arg.num_philosophers = ft_atoi(argv[1]);
	main_aux->arg.philosophers = main_aux->philosophers;
	main_aux->arg.threads = main_aux->threads;
	pthread_mutex_init(&main_aux->arg.print_mutex, NULL);
	pthread_mutex_init(&main_aux->arg.dead_mutex, NULL);
	pthread_mutex_init(&main_aux->arg.last_to_eat_mutex, NULL);
	main_aux->arg.start_time = get_current_time();
	return (0);
}

int	main(int argc, char *argv[])
{
	t_main_aux	aux;
	pthread_t	monitor_thread;

	if (validate_args(argc, argv) != -1)
		return (1);
	init_main_aux(argc, argv, &aux);
	create_filosof(ft_atoi(argv[2]), ft_atoi(argv[3]),
		ft_atoi(argv[4]), &aux.arg);
	pthread_create(&monitor_thread, NULL, philo_monitor, &aux.arg);
	join_threads(aux.threads, monitor_thread, aux.arg.num_philosophers);
	cleanup(&aux.arg);
	free(aux.forks);
	free(aux.threads);
	free(aux.philosophers);
	return (0);
}
