/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 12:00:21 by hpatsi            #+#    #+#             */
/*   Updated: 2024/02/28 09:29:47 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	destroy_forks(t_args *args)
{
	int	i;

	i = 0;
	while (i < args->philo_count)
	{
		pthread_mutex_destroy(&args->forks[i]);
		i++;
	}
	free(args->forks);
	return (1);
}

int	initialize_forks(t_args *args)
{
	int	i;

	args->forks = malloc(args->philo_count * sizeof(pthread_mutex_t));
	if (args->forks == 0)
		return (-1);
	i = 0;
	while (i < args->philo_count)
	{
		pthread_mutex_init(&args->forks[i], NULL);
		i++;
	}
	return (1);
}

int	initialize_philosophers(pthread_t *threads, t_args *args)
{
	t_philo	*philos;
	int		i;

	philos = malloc(args->philo_count * sizeof(t_philo));
	if (philos == 0)
		return (-1);
	i = 0;
	while (i < args->philo_count)
	{
		philos[i].num = i;
		philos[i].args = args;
		philos[i].eat_count = 0;
		if (gettimeofday(&philos[i].last_eat_time, NULL) == -1)
		{
			free(philos);
			return (-1);
		}
		pthread_create(&threads[i], NULL, &philo_start, &philos[i]);
		i++;
	}
	free(philos);
	return (1);
}

int	initialize_threads(t_args *args)
{
	pthread_t	*threads;
	int			i;

	threads = malloc(args->philo_count * sizeof(pthread_t));
	if (threads == 0)
		return (-1);
	if (initialize_philosophers(threads, args) == -1)
	{
		free(threads);
		return (-1);
	}
	i = 0;
	while (i < args->philo_count)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	destroy_forks(args);
	free(threads);
	return (1);
}
