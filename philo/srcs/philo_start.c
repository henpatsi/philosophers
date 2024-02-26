/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_start.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 09:15:23 by hpatsi            #+#    #+#             */
/*   Updated: 2024/02/26 12:48:11 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	eat(t_philo *philo)
{
	philo->state = EAT;
	print_state(*philo);

	usleep(philo->args->eat_time * 1000);
	
	philo->state = SLEEP;
	print_state(*philo);

	return (1);
}

int	pick_up_forks(t_philo *philo)
{
	pthread_mutex_t	fork_right;
	pthread_mutex_t	fork_left;
	int				ret;

	fork_right = philo->args->forks[philo->num];
	if (philo->num == 0)
		fork_left = philo->args->forks[philo->args->philo_count - 1];
	else
		fork_left = philo->args->forks[philo->num - 1];
	ret = pthread_mutex_lock(&fork_right);
	printf("ret = %d\n", ret);
	print_fork(*philo);
	ret = pthread_mutex_lock(&fork_left);
	printf("ret = %d\n", ret);
	print_fork(*philo);
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
