/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   better_sleep_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 08:49:26 by hpatsi            #+#    #+#             */
/*   Updated: 2024/03/14 13:47:30 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	philo_die(t_args args, t_philo *philo)
{
	sem_wait(philo->sems.write);
	if (!get_exit_state(philo))
		printf("%ld %d died\n", get_time_passed(args.start_time), philo->num + 1);
	sem_post(philo->sems.dead);
	if (philo->state == EAT)
		put_down_forks(philo);
	usleep(1000);
	sem_post(philo->sems.write);
	return (-1);
}

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

int	better_sleep(t_args args, t_philo *philo, long sleep_time)
{
	t_timeval	sleep_start;

	if (gettimeofday(&sleep_start, NULL) == -1)
		return (-1);
	while (get_time_passed(sleep_start) < sleep_time)
	{
		usleep(200);
		if (get_exit_state(philo))
		{
			if (philo->state == EAT)
				put_down_forks(philo);
			return (-1);
		}
		if (get_time_passed(philo->last_eat_time) > args.die_time)
			return (philo_die(args, philo));
	}
	return (1);
}
