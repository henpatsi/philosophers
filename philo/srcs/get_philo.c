/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 11:27:37 by hpatsi            #+#    #+#             */
/*   Updated: 2024/03/05 12:31:39 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	get_time_passed(t_timeval start_time)
{
	t_timeval	time;
	long		ms;

	if (gettimeofday(&time, NULL) == -1)
		return (-1);
	ms = (time.tv_sec - start_time.tv_sec) * 1000;
	ms += (time.tv_usec - start_time.tv_usec) / 1000;
	return (ms);
}

int	get_philo_eat_count(t_philo *philo, t_mutex *philo_mutex)
{
	int	ret;

	pthread_mutex_lock(philo_mutex);
	ret = philo->eat_count;
	pthread_mutex_unlock(philo_mutex);
	return (ret);
}

t_timeval	get_philo_eat_time(t_philo *philo, t_mutex *philo_mutex)
{
	t_timeval	ret;

	pthread_mutex_lock(philo_mutex);
	ret = philo->last_eat_time;
	pthread_mutex_unlock(philo_mutex);
	return (ret);
}

int	get_philo_exiting(t_philo *philo, t_mutex *philo_mutex)
{
	int	ret;

	pthread_mutex_lock(philo_mutex);
	ret = philo->exiting;
	pthread_mutex_unlock(philo_mutex);
	return (ret);
}
