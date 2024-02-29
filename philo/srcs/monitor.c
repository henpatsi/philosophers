/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 09:34:25 by hpatsi            #+#    #+#             */
/*   Updated: 2024/02/29 13:28:44 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

nt	monitor_start(t_args args, t_mutexes mutexes, t_philo *philos, pthread_t *threads)
{
	int	i;
	(void) philos;

	i = 0;
	while (i < args.philo_count)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	return (0);
}
