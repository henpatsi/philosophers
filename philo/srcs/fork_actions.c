/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_actions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 14:49:10 by hpatsi            #+#    #+#             */
/*   Updated: 2024/02/26 15:55:07 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	put_down_forks(t_philo *philo)
{
	pthread_mutex_t	*fork_right;
	pthread_mutex_t	*fork_left;

	fork_right = &philo->args->forks[philo->num];
	if (philo->num == 0)
		fork_left = &philo->args->forks[philo->args->philo_count - 1];
	else
		fork_left = &philo->args->forks[philo->num - 1];
	pthread_mutex_unlock(fork_right);
	pthread_mutex_unlock(fork_left);
	return (1);
}

int	pick_up_forks(t_philo *philo)
{
	pthread_mutex_t	*fork_right;
	pthread_mutex_t	*fork_left;

	fork_right = &philo->args->forks[philo->num];
	if (philo->num == 0)
		fork_left = &philo->args->forks[philo->args->philo_count - 1];
	else
		fork_left = &philo->args->forks[philo->num - 1];
	pthread_mutex_lock(fork_right);
	print_fork(*philo);
	pthread_mutex_lock(fork_left);
	print_fork(*philo);
	return (1);
}
