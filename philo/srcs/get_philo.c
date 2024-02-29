/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 11:27:37 by hpatsi            #+#    #+#             */
/*   Updated: 2024/02/29 12:43:30 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	get_philo_eat_count(t_philo *philo, pthread_mutex_t *philo_mutex)
{
	int	ret;

	pthread_mutex_lock(philo_mutex);
	ret = philo->eat_count;
	pthread_mutex_unlock(philo_mutex);
	return (ret);
}

struct timeval	get_philo_eat_time(t_philo *philo, pthread_mutex_t *philo_mutex)
{
	struct timeval	ret;

	pthread_mutex_lock(philo_mutex);
	ret = philo->last_eat_time;
	pthread_mutex_unlock(philo_mutex);
	return (ret);
}

t_state	get_philo_state(t_philo *philo, pthread_mutex_t *philo_mutex)
{
	t_state	ret;

	pthread_mutex_lock(philo_mutex);
	ret = philo->state;
	pthread_mutex_unlock(philo_mutex);
	return (ret);
}
