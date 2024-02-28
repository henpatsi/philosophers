/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_start.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 09:15:23 by hpatsi            #+#    #+#             */
/*   Updated: 2024/02/28 10:48:31 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	philo_loop(t_philo philo)
{
	while (philo.args->eat_count == 0 || philo.eat_count < philo.args->eat_count)
	{
		if (pick_up_forks(&philo) == -1)
			break ;
		if (philo_eat(&philo) == -1)
			break ;
		if (philo.eat_count == philo.args->eat_count)
			break ;
		if (philo_sleep(&philo) == -1)
			break ;
		philo_think(&philo);
	}
}

void	*philo_start(void *arg)
{
	t_philo	philo;

	philo = *(t_philo *) arg;
	if (philo.num % 2 == 0)
	{
		philo_think(&philo);
		usleep(100);
	}
	philo_loop(philo);
	return (0);
}
