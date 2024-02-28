/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   better_sleep.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 08:49:26 by hpatsi            #+#    #+#             */
/*   Updated: 2024/02/28 09:19:18 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	better_sleep(t_philo *philo, long sleep_time)
{
	struct timeval	sleep_start;

	if (gettimeofday(&sleep_start, NULL) == -1)
		return (-1);
	while (get_time_passed(sleep_start) < sleep_time)
	{
		usleep(200);
		if (get_time_passed(philo->last_eat_time) > philo->args->die_time)
		{
			philo_die(philo);
			return (-1);
		}
	}
	return (1);
}
