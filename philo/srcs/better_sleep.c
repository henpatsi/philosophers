/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   better_sleep.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 08:49:26 by hpatsi            #+#    #+#             */
/*   Updated: 2024/02/29 13:17:56 by hpatsi           ###   ########.fr       */
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
		if (get_time_passed(get_philo_eat_time(input.philo, input.philo_mutex)) > input.args.die_time)
		{
			if (get_philo_state(input.philo, input.philo_mutex) == EAT)
				put_down_forks(input);
			philo_die(input);
			return (-1);
		}
	}
	return (1);
}
