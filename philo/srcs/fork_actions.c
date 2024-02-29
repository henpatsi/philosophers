/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_actions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 14:49:10 by hpatsi            #+#    #+#             */
/*   Updated: 2024/02/29 10:06:55 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	one_fork_death(t_philo *philo, t_args args, t_mutexes *mutexes, pthread_mutex_t *fork)
{
	better_sleep(philo, args, mutexes, args.die_time * 2);
	pthread_mutex_unlock(fork);
	return (-1);
}

int	put_down_forks(t_philo *philo, t_args args, t_mutexes *mutexes)
{
	pthread_mutex_t	*fork_right;
	pthread_mutex_t	*fork_left;

	fork_right = &mutexes->forks[philo->num];
	if (philo->num == 0)
		fork_left = &mutexes->forks[args.philo_count - 1];
	else
		fork_left = &mutexes->forks[philo->num - 1];
	pthread_mutex_unlock(fork_right);
	pthread_mutex_unlock(fork_left);
	return (1);
}

int	pick_up_forks(t_philo *philo, t_args args, t_mutexes *mutexes)
{
	pthread_mutex_t	*fork_right;
	pthread_mutex_t	*fork_left;

	fork_right = &mutexes->forks[philo->num];
	if (philo->num == 0)
		fork_left = &mutexes->forks[args.philo_count - 1];
	else
		fork_left = &mutexes->forks[philo->num - 1];
	pthread_mutex_lock(fork_right);
	print_fork(*philo, args);
	if (args.philo_count == 1)
		return (one_fork_death(philo, args, mutexes, fork_right));
	pthread_mutex_lock(fork_left);
	print_fork(*philo, args);
	return (1);
}
