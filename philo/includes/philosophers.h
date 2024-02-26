/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 10:04:31 by hpatsi            #+#    #+#             */
/*   Updated: 2024/02/26 14:53:34 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

typedef enum e_state
{
	EAT,
	SLEEP,
	THINK,
	DEAD,
}	t_state;

typedef struct s_args
{
	int				philo_count;
	int				die_time;
	int				eat_time;
	int				sleep_time;
	int				eat_count;
	struct timeval	start_time;
	pthread_mutex_t	*forks;
}	t_args;

typedef struct s_philo
{
	int				num;
	struct timeval	last_eat_time;
	t_state			state;
	t_args			*args;
}	t_philo;

int		initialize_forks(t_args *args);
int		initialize_threads(t_args *args);

void	*philo_start(void *arg);
int		philo_eat(t_philo *philo);
int		philo_sleep(t_philo *philo);
int		philo_think(t_philo *philo);

int		put_down_forks(t_philo *philo);
int		pick_up_forks(t_philo *philo);

void	*monitor_start(void *arg);

long	get_time_passed(struct timeval start_time);
int		print_fork(t_philo philo);
int		print_state(t_philo philo);

int		ft_atoi(const char *str);

#endif
