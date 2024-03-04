/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_actions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 14:49:10 by hpatsi            #+#    #+#             */
/*   Updated: 2024/03/04 09:21:08 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	print_fork(t_thread_input input)
{
	long	ms;

	ms = get_time_passed(input.args.start_time);
	if (ms == -1)
		return (-1);
	printf("%ld %d %s\n", ms, input.num + 1, "has taken a fork");
	return (1);
}

int	one_fork_death(t_thread_input input)
{
	better_sleep(input, input.args.die_time * 2);
	pthread_mutex_unlock(input.right_fork);
	return (-1);
}

int	put_down_forks(t_thread_input input)
{
	pthread_mutex_unlock(input.right_fork);
	pthread_mutex_unlock(input.left_fork);
	return (1);
}

int	pick_up_forks(t_thread_input input)
{
	pthread_mutex_lock(input.right_fork);
	if (get_philo_state(input.philo, input.philo_mutex) == DEAD
		|| input.philo->exiting)
	{
		pthread_mutex_unlock(input.right_fork);
		return (-1);
	}
	print_fork(input);
	if (input.args.philo_count == 1)
		return (one_fork_death(input));
	pthread_mutex_lock(input.left_fork);
	if (get_philo_state(input.philo, input.philo_mutex) == DEAD
		|| input.philo->exiting)
	{
		pthread_mutex_unlock(input.right_fork);
		pthread_mutex_unlock(input.left_fork);
		return (-1);
	}
	print_fork(input);
	return (1);
}
