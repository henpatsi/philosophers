/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   better_sleep.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 08:49:26 by hpatsi            #+#    #+#             */
/*   Updated: 2024/03/05 12:56:09 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	better_sleep(t_thread_input input, long sleep_time)
{
	t_timeval	sleep_start;

	if (gettimeofday(&sleep_start, NULL) == -1)
		return (-1);
	while (get_time_passed(sleep_start) < sleep_time)
	{
		usleep(200);
		if (get_philo_exiting(input.philo, input.philo_mutex))
		{
			if (input.state == EAT)
				put_down_forks(input);
			return (-1);
		}
	}
	return (1);
}
