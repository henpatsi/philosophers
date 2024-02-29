/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 14:48:37 by hpatsi            #+#    #+#             */
/*   Updated: 2024/02/29 11:13:44 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	philo_die(t_thread_input input)
{
	input.philo->state = DEAD;
	print_state(input);
	return (1);
}

int	philo_eat(t_thread_input input)
{
	input.philo->state = EAT;
	print_state(input);
	input.philo->eat_count++;
	if (gettimeofday(&input.philo->last_eat_time, NULL) == -1)
		return (-1);
	if (better_sleep(input, input.args.eat_time) == -1)
		return (-1);
	put_down_forks(input);
	return (1);
}

int	philo_sleep(t_thread_input input)
{
	input.philo->state = SLEEP;
	print_state(input);
	if (better_sleep(input, input.args.sleep_time) == -1)
		return (-1);
	return (1);
}

int	philo_think(t_thread_input input)
{
	input.philo->state = THINK;
	print_state(input);
	return (1);
}
