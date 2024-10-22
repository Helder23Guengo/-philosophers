/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguengo <hguengo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 09:35:40 by hguengo           #+#    #+#             */
/*   Updated: 2024/10/21 13:09:55 by hguengo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_arg	t_arg;
typedef struct s_philosopher
{
	int				id;
	long			last_to_eat;
	int				meals;
	int				full;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_arg			*arg;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	char			*argv[];
}t_philosopher;

struct s_arg
{
	int				max_meals;
	int				is_dead;
	long			start_time;
	int				num_philosophers;
	t_philosopher	*philosophers;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	dead_mutex;
	pthread_mutex_t	last_to_eat_mutex;
	pthread_mutex_t	*forks;
	pthread_mutex_t	data_mutex;
	pthread_t		*threads;
};

typedef struct s_main_aux
{
	t_philosopher	*philosophers;
	pthread_mutex_t	*forks;
	t_arg			arg;
	pthread_t		*threads;
}t_main_aux;

int		get_current_last(size_t time);
long	get_current_time(void);
int		ft_atoi(const char *str);
void	*philo_monitor(void *args);
int		is_all_full(t_philosopher *philo);
int		print_status(t_philosopher *philo, const char *status);
int		live(t_arg *argay);
int		time_to_eat_utils(t_philosopher *philo);
int		time_to_die(t_philosopher *philo, t_arg *argay);
int		time_to_eat(t_philosopher *philo);
int		validate_args(int argc, char *argv[]);
int		is_negative(char *str);
void	monitors(void *arg);
void	*philo_life(void *arg);
void	cleanup(t_arg *arg);
// void	low_unlock(t_philosopher *philo);
#endif
