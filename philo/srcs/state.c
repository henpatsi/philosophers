/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 10:57:37 by hpatsi            #+#    #+#             */
/*   Updated: 2024/02/26 12:58:02 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	get_time_passed(struct timeval start_time)
{
	struct timeval	time;
	long			ms;

	if (gettimeofday(&time, NULL) == -1)
		return (-1);
	ms = (time.tv_sec - start_time.tv_sec) * 1000;
	ms += (time.tv_usec - start_time.tv_usec) / 1000;
	return (ms);
}

int	print_fork(t_philo philo)
{
	long	ms;

	ms = get_time_passed(philo.args->start_time);
	if (ms == -1)
		return (-1);
	printf("%ld %d %s\n", ms, philo.num + 1, "has taken a fork");
	return (1);
}

int	print_state(t_philo philo)
{
	long	ms;
	char	*state_str;

	ms = get_time_passed(philo.args->start_time);
	if (ms == -1)
		return (-1);
	if (philo.state == EAT)
		state_str = "is eating";
	else if (philo.state == SLEEP)
		state_str = "is sleeping";
	else if (philo.state == THINK)
		state_str = "is thinking";
	else if (philo.state == DEAD)
		state_str = "died";
	else
		state_str = "";
	printf("%ld %d %s\n", ms, philo.num + 1, state_str);
	return (1);
}
