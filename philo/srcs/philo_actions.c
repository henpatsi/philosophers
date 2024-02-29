/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 14:48:37 by hpatsi            #+#    #+#             */
/*   Updated: 2024/02/29 10:06:29 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	philo_die(t_philo *philo, t_args args, t_mutexes *mutexes)
{
	(void) mutexes;
	philo->state = DEAD;
	print_state(*philo, args);
	return (1);
}

int	philo_eat(t_philo *philo, t_args args, t_mutexes *mutexes)
{
	philo->state = EAT;
	print_state(*philo, args);
	philo->eat_count++;
	if (gettimeofday(&philo->last_eat_time, NULL) == -1)
		return (-1);
	if (better_sleep(philo, args, mutexes, args.eat_time) == -1)
		return (-1);
	put_down_forks(philo, args, mutexes);
	return (1);
}

int	philo_sleep(t_philo *philo, t_args args, t_mutexes *mutexes)
{
	(void) mutexes;
	philo->state = SLEEP;
	print_state(*philo, args);
	if (better_sleep(philo, args, mutexes, args.sleep_time) == -1)
		return (-1);
	return (1);
}

int	philo_think(t_philo *philo, t_args args, t_mutexes *mutexes)
{
	(void) mutexes;
	philo->state = THINK;
	print_state(*philo, args);
	return (1);
}
