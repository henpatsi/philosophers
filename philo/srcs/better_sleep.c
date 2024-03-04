/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   better_sleep.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 08:49:26 by hpatsi            #+#    #+#             */
/*   Updated: 2024/03/04 10:41:24 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	philo_has_died(t_args args, t_philo *philo, t_mutex *philo_mutex)
{
	t_timeval	time_since_eat;

	time_since_eat = get_philo_eat_time(philo, philo_mutex);
	if (get_time_passed(time_since_eat) > args.die_time)
		return (1);
	return (0);
}

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
			if (get_philo_state(input.philo, input.philo_mutex) == EAT)
				put_down_forks(input);
			return (-1);
		}
	}
	return (1);
}
