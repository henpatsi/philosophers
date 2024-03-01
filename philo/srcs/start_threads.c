/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 10:43:28 by hpatsi            #+#    #+#             */
/*   Updated: 2024/03/01 10:47:38 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	start_threads(t_args args, t_mutexes mutexes,
		t_philo *philos, t_thread_input *inputs)
{
	pthread_t	*threads;
	int			i;

	threads = malloc(args.philo_count * sizeof(pthread_t));
	if (threads == 0)
		return (-1);
	i = 0;
	while (i < args.philo_count)
	{
		pthread_create(&threads[i], NULL, &philo_start, &inputs[i]);
		i++;
	}
	return (monitor_start(args, mutexes.philos, philos, threads));
}
