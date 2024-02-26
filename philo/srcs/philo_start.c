/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_start.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 09:15:23 by hpatsi            #+#    #+#             */
/*   Updated: 2024/02/26 14:50:26 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*philo_start(void *arg)
{
	t_philo	philo;

	philo = *(t_philo *) arg;
	
	if (philo.num % 2 == 0)
		philo_think(&philo);
	pick_up_forks(&philo);
	philo_eat(&philo);
	philo_sleep(&philo);

	return (0);
}
