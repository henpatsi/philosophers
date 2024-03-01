/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 09:34:25 by hpatsi            #+#    #+#             */
/*   Updated: 2024/03/01 10:15:45 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	join_threads(pthread_t *threads, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	return (1);
}

int	set_all_philos_exiting(t_args args, t_mutexes mutexes, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < args.philo_count)
	{
		set_philo_exiting(&philos[i], &mutexes.philos[i]);
		i++;
	}
	return (1);
}

int	all_finished(t_args args, t_mutexes mutexes, t_philo *philos, pthread_t *threads)
{
	int	i;
	int	philo_eat_count;

	i = 0;
	while (i < args.philo_count)
	{
		philo_eat_count = get_philo_eat_count(&philos[i], &mutexes.philos[i]);
		if (philo_eat_count < args.eat_count)
			return (0);
		i++;
	}
	set_all_philos_exiting(args, mutexes, philos);
	join_threads(threads, args.philo_count);
	return (1);
}

int	philo_dead(t_args args, t_mutexes mutexes, t_philo *philos, pthread_t *threads)
{
	int	i;

	i = 0;
	while (i < args.philo_count)
	{
		if (get_philo_state(&philos[i], &mutexes.philos[i]) == DEAD)
		{
			set_all_philos_exiting(args, mutexes, philos);
			join_threads(threads, args.philo_count);
			return (1);
		}
		i++;
	}
	return (0);
}

int	monitor_start(t_args args, t_mutexes mutexes, t_philo *philos, pthread_t *threads)
{
	while (1)
	{
		usleep(100);
		if (args.eat_count > 0 && all_finished(args, mutexes, philos, threads))
			break ;
		if (philo_dead(args, mutexes, philos, threads))
			break;
	}
	return (0);
}
