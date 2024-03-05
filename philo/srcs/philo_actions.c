/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 14:48:37 by hpatsi            #+#    #+#             */
/*   Updated: 2024/03/05 12:55:41 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	philo_eat(t_thread_input input)
{
	set_philo_state(&input, EAT);
	increment_philo_eat_count(input.philo, input.philo_mutex);
	set_philo_last_eat(input.philo, input.philo_mutex);
	if (better_sleep(input, input.args.eat_time) == -1)
		return (-1);
	put_down_forks(input);
	return (1);
}

int	philo_sleep(t_thread_input input)
{
	set_philo_state(&input, SLEEP);
	if (better_sleep(input, input.args.sleep_time) == -1)
		return (-1);
	return (1);
}

int	philo_think(t_thread_input input)
{
	set_philo_state(&input, THINK);
	return (1);
}
