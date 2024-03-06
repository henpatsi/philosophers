/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_actions_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 14:49:10 by hpatsi            #+#    #+#             */
/*   Updated: 2024/03/06 13:39:09 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	print_fork(t_args args, t_philo *philo)
{
	long	ms;

	ms = get_time_passed(args.start_time);
	if (ms == -1)
		return (-1);
	printf("%ld %d %s\n", ms, philo->num + 1, "has taken a fork");
	return (1);
}

// int	one_fork_death(t_thread_input input)
// {
// 	better_sleep(input, input.args.die_time * 2);
// 	pthread_mutex_unlock(input.right_fork);
// 	return (-1);
// }

int	put_down_forks(t_philo *philo)
{
	sem_post(philo->forks);
	sem_post(philo->forks);
	return (1);
}

int	pick_up_forks(t_args args, t_philo *philo)
{
	sem_wait(philo->forks);
	print_fork(args, philo);
	sem_wait(philo->forks);
	print_fork(args, philo);
	return (1);
}
