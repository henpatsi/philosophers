/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 14:48:37 by hpatsi            #+#    #+#             */
/*   Updated: 2024/02/26 15:55:12 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	philo_eat(t_philo *philo)
{
	philo->state = EAT;
	print_state(*philo);
	usleep(philo->args->eat_time * 1000);
	put_down_forks(philo);
	if (gettimeofday(&philo->last_eat_time, NULL) == -1)
		return (-1);
	return (1);
}

int	philo_sleep(t_philo *philo)
{
	philo->state = SLEEP;
	print_state(*philo);
	usleep(philo->args->sleep_time * 1000);
	return (1);
}

int	philo_think(t_philo *philo)
{
	philo->state = THINK;
	print_state(*philo);
	usleep(100);
	return (1);
}
