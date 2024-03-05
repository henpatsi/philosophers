/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 10:04:31 by hpatsi            #+#    #+#             */
/*   Updated: 2024/03/05 13:11:56 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct timeval	t_timeval;
typedef pthread_mutex_t	t_mutex;

typedef enum e_state
{
	EAT,
	SLEEP,
	THINK,
}	t_state;

typedef struct s_args
{
	int			philo_count;
	int			die_time;
	int			eat_time;
	int			sleep_time;
	int			eat_count;
	t_timeval	start_time;
}	t_args;

typedef struct s_mutexes
{
	t_mutex	*forks;
	t_mutex	*philos;
}	t_mutexes;

typedef struct s_philo
{
	int			eat_count;
	t_timeval	last_eat_time;
	int			exiting;
}	t_philo;

typedef struct s_thread_input
{
	int		num;
	t_state	state;
	t_philo	*philo;
	t_args	args;
	t_mutex	*philo_mutex;
	t_mutex	*left_fork;
	t_mutex	*right_fork;
}	t_thread_input;

int			prepare_args(t_args	*args, int argc, char **argv);
int			prepare_mutexes(t_mutexes *mutexes, t_args args);
int			prepare_philosophers(t_philo **philos, t_args args);
int			prepare_inputs(t_thread_input **inputs, t_args args,
				t_mutexes mutexes, t_philo *philos);

int			initialize_mutex_list(t_mutex **dst, t_args args);
void		destroy_mutex_list(t_mutex **dst, t_args args);
void		destroy_all_mutex(t_mutexes *mutexes, t_args args);

int			start_threads(t_args args, t_mutexes mutexes,
				t_philo *philos, t_thread_input *inputs);
void		*philo_start(void *arg);
int			monitor_start(t_args args, t_mutex *philo_mutexes,
				t_philo *philos, pthread_t *threads);

int			philo_eat(t_thread_input input);
int			philo_sleep(t_thread_input input);
int			philo_think(t_thread_input input);

int			pick_up_forks(t_thread_input input);
int			put_down_forks(t_thread_input input);

int			get_philo_eat_count(t_philo *philo, t_mutex *philo_mutex);
t_timeval	get_philo_eat_time(t_philo *philo, t_mutex *philo_mutex);
int			get_philo_exiting(t_philo *philo, t_mutex *philo_mutex);

int			increment_philo_eat_count(t_philo *philo, t_mutex *philo_mutex);
int			set_philo_last_eat(t_philo *philo, t_mutex *philo_mutex);
int			set_philo_state(t_thread_input *input, t_state state);
int			set_philo_exiting(t_philo *philo, t_mutex *philo_mutex);

long		get_time_passed(t_timeval start_time);
int			better_sleep(t_thread_input input, long sleep_time);
int			extract_arg(int	*dst, const char *str);

#endif
