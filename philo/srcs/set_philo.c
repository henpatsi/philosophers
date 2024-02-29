/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 11:37:38 by hpatsi            #+#    #+#             */
/*   Updated: 2024/02/29 12:41:29 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	increment_philo_eat_count(t_philo *philo, pthread_mutex_t *philo_mutex)
{
	pthread_mutex_lock(philo_mutex);
	philo->eat_count++;
	pthread_mutex_unlock(philo_mutex);
	return (1);
}

int	set_philo_last_eat(t_philo *philo, pthread_mutex_t *philo_mutex)
{
	pthread_mutex_lock(philo_mutex);
	if (gettimeofday(&philo->last_eat_time, NULL) == -1)
	{
		pthread_mutex_unlock(philo_mutex);
		return (-1);
	}
	pthread_mutex_unlock(philo_mutex);
	return (1);
}

int	set_philo_state(t_philo *philo, pthread_mutex_t *philo_mutex, t_state state)
{
	pthread_mutex_lock(philo_mutex);
	philo->state = state;
	pthread_mutex_unlock(philo_mutex);
	return (1);
}
