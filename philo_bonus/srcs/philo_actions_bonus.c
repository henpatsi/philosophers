/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 14:48:37 by hpatsi            #+#    #+#             */
/*   Updated: 2024/03/06 13:48:51 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	philo_eat(t_args args, t_philo *philo)
{
	set_philo_state(args, philo, EAT);
	philo->eat_count++;
	gettimeofday(&philo->last_eat_time, NULL);
	if (better_sleep(args, philo, args.eat_time) == -1)
		return (-1);
	put_down_forks(philo);
	return (1);
}

int	philo_sleep(t_args args, t_philo *philo)
{
	set_philo_state(args, philo, SLEEP);
	if (better_sleep(args, philo, args.sleep_time) == -1)
		return (-1);
	return (1);
}
