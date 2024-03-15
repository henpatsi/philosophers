/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 09:34:25 by hpatsi            #+#    #+#             */
/*   Updated: 2024/03/15 11:44:09 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	philo_has_died(t_args args, t_philo *philo, t_mutex *philo_mutex)
{
	t_timeval	time_since_eat;

	time_since_eat = get_philo_eat_time(philo, philo_mutex);
	if (get_time_passed(time_since_eat) > args.die_time)
		return (1);
	return (0);
}

void	set_all_philos_exiting(t_philo *philos, t_mutex *philo_mutexes,
		pthread_t *threads, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		set_philo_exiting(&philos[i], &philo_mutexes[i]);
		i++;
	}
	i = 0;
	while (i < count)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
}

int	all_finished(t_args args, t_philo *philos,
		t_mutex *philo_mutexes, pthread_t *threads)
{
	int	i;
	int	philo_eat_count;

	i = 0;
	while (i < args.philo_count)
	{
		philo_eat_count = get_philo_eat_count(&philos[i], &philo_mutexes[i]);
		if (philo_eat_count < args.eat_count)
			return (0);
		i++;
	}
	set_all_philos_exiting(philos, philo_mutexes, threads, args.philo_count);
	return (1);
}

int	philo_dead(t_args args, t_philo *philos,
		t_mutex *philo_mutexes, pthread_t *threads)
{
	int	i;

	i = 0;
	while (i < args.philo_count)
	{
		if (philo_has_died(args, &philos[i], &philo_mutexes[i]))
		{
			printf("%ld %d died\n", get_time_passed(args.start_time), i + 1);
			set_all_philos_exiting(philos, philo_mutexes,
				threads, args.philo_count);
			return (1);
		}
		i++;
	}
	return (0);
}

void	monitor_start(t_args args, t_mutex *philo_mutexes,
		t_philo *philos, pthread_t *threads)
{
	while (1)
	{
		usleep(200);
		if (args.eat_count != 0)
		{
			if (all_finished(args, philos, philo_mutexes, threads))
				break ;
		}
		if (philo_dead(args, philos, philo_mutexes, threads))
			break ;
	}
}
