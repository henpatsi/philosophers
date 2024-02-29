/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 12:00:21 by hpatsi            #+#    #+#             */
/*   Updated: 2024/02/29 09:08:01 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	create_threads(t_philo *philos, pthread_t *threads, t_args *args)
{
	int	i;

	i = 0;
	while (i < args->philo_count)
	{
		pthread_create(&threads[i], NULL, &philo_start, &philos[i]);
		i++;
	}
	monitor_start(philos, threads, args);
	return (1);
}

int	initialize_philosophers(t_philo **philos, t_args *args)
{
	int	i;

	*philos = malloc(args->philo_count * sizeof(t_philo));
	if (*philos == 0)
		return (-1);
	i = 0;
	while (i < args->philo_count)
	{
		(*philos)[i].num = i;
		(*philos)[i].args = args;
		(*philos)[i].eat_count = 0;
		(*philos)[i].state = THINK;
		if (gettimeofday(&(*philos)[i].last_eat_time, NULL) == -1)
		{
			free((*philos));
			return (-1);
		}
		i++;
	}
	return (1);
}

int	initialize_threads(t_args *args)
{
	pthread_t	*threads;
	t_philo		*philos;

	threads = malloc(args->philo_count * sizeof(pthread_t));
	if (threads == 0)
		return (-1);
	if (initialize_philosophers(&philos, args) == -1)
	{
		free(philos);
		free(threads);
		return (-1);
	}
	create_threads(philos, threads, args);
	free(philos);
	free(threads);
	return (1);
}
