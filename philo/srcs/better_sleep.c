/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   better_sleep.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 08:49:26 by hpatsi            #+#    #+#             */
/*   Updated: 2024/02/29 11:07:33 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	better_sleep(t_thread_input input, long sleep_time)
{
	struct timeval	sleep_start;

	if (gettimeofday(&sleep_start, NULL) == -1)
		return (-1);
	while (get_time_passed(sleep_start) < sleep_time)
	{
		usleep(200);
		if (get_time_passed(input.philo->last_eat_time) > input.args.die_time)
		{
			philo_die(input);
			return (-1);
		}
	}
	return (1);
}
