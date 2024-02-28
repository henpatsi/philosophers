/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 14:48:37 by hpatsi            #+#    #+#             */
/*   Updated: 2024/02/28 09:11:00 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	philo_die(t_philo *philo)
{
	philo->state = DEAD;
	print_state(*philo);
	return (1);
}

int	philo_eat(t_philo *philo)
{
	philo->state = EAT;
	print_state(*philo);
	philo->eat_count++;
	if (gettimeofday(&philo->last_eat_time, NULL) == -1)
		return (-1);
	if (better_sleep(philo, philo->args->eat_time) == -1)
		return (-1);
	put_down_forks(philo);
	return (1);
}

int	philo_sleep(t_philo *philo)
{
	philo->state = SLEEP;
	print_state(*philo);
	if (better_sleep(philo, philo->args->sleep_time) == -1)
		return (-1);
	return (1);
}

int	philo_think(t_philo *philo)
{
	philo->state = THINK;
	print_state(*philo);
	return (1);
}
