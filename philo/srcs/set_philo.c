/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 11:37:38 by hpatsi            #+#    #+#             */
/*   Updated: 2024/03/04 12:02:03 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	print_state(t_thread_input input, t_state state)
{
	long	ms;
	char	*state_str;

	ms = get_time_passed(input.args.start_time);
	if (ms == -1)
		return (-1);
	if (state == EAT)
		state_str = "is eating";
	else if (state == SLEEP)
		state_str = "is sleeping";
	else if (state == THINK)
		state_str = "is thinking";
	else
		state_str = "";
	printf("%ld %d %s\n", ms, input.num + 1, state_str);
	return (1);
}

int	increment_philo_eat_count(t_philo *philo, t_mutex *philo_mutex)
{
	pthread_mutex_lock(philo_mutex);
	philo->eat_count++;
	pthread_mutex_unlock(philo_mutex);
	return (1);
}

int	set_philo_last_eat(t_philo *philo, t_mutex *philo_mutex)
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

int	set_philo_state(t_thread_input input, t_state state)
{
	pthread_mutex_lock(input.philo_mutex);
	input.philo->state = state;
	pthread_mutex_unlock(input.philo_mutex);
	print_state(input, state);
	return (1);
}

int	set_philo_exiting(t_philo *philo, t_mutex *philo_mutex)
{
	pthread_mutex_lock(philo_mutex);
	philo->exiting = 1;
	pthread_mutex_unlock(philo_mutex);
	return (1);
}
