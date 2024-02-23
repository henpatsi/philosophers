/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 10:04:31 by hpatsi            #+#    #+#             */
/*   Updated: 2024/02/23 11:41:56 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

typedef enum e_state
{
	EAT,
	SLEEP,
	THINK,
}	t_state;

typedef struct s_args
{
	int	philo_count;
	int	die_time;
	int	eat_time;
	int	sleep_time;
	int	eat_count;
}	t_args;

typedef struct s_philo
{
	int		num;
	t_state	state;
	t_args	args;
}	t_philo;

int		ft_atoi(const char *str);

long	get_time_passed(struct timeval start_time);

#endif
