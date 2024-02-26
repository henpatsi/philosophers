/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_start.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 09:15:23 by hpatsi            #+#    #+#             */
/*   Updated: 2024/02/26 12:57:35 by hpatsi           ###   ########.fr       */
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

int	eat(t_philo *philo)
{
	philo->state = EAT;
	print_state(*philo);

	usleep(philo->args->eat_time * 1000);
	
	put_down_forks(philo);

	philo->state = SLEEP;
	print_state(*philo);

	return (1);
}

void	*philo_start(void *arg)
{
	t_philo	philo;

	philo = *(t_philo *) arg;
	
	pick_up_forks(&philo);
	eat(&philo);

	return (0);
}
