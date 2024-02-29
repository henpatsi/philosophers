/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 09:34:25 by hpatsi            #+#    #+#             */
/*   Updated: 2024/02/29 13:20:10 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	monitor_start(t_philo *philos, pthread_t *threads, t_thread_input *inputs)
{
	int	i;
	(void) philos;

	i = 0;
	while (i < inputs->args.philo_count)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	return (0);
}
