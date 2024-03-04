/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 10:04:31 by hpatsi            #+#    #+#             */
/*   Updated: 2024/03/04 15:22:19 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

#include <sys/stat.h>
#include <semaphore.h>

typedef struct timeval	t_timeval;

typedef enum e_state
{
	EAT,
	SLEEP,
	THINK,
	DEAD,
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

typedef struct s_philo
{
	int			eat_count;
	t_timeval	last_eat_time;
	t_state		state;
	int			exiting;
}	t_philo;

int			prepare_args(t_args	*args, int argc, char **argv);
int			prepare_philosophers(t_philo **philos, t_args args);
int			extract_arg(int	*dst, const char *str);

int			start_processes(t_args args, sem_t *forks, t_philo *philos);

#endif
