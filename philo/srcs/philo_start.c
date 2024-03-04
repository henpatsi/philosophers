/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_start.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 09:15:23 by hpatsi            #+#    #+#             */
/*   Updated: 2024/03/04 09:54:13 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	philo_loop(t_thread_input input)
{
	while (!get_philo_exiting(input.philo, input.philo_mutex))
	{
		if (pick_up_forks(input) == -1)
			break ;
		if (philo_eat(input) == -1)
			break ;
		if (philo_sleep(input) == -1)
			break ;
		philo_think(input);
	}
}

void	*philo_start(void *arg)
{
	t_thread_input	input;

	input = *(t_thread_input *) arg;
	set_philo_last_eat(input.philo, input.philo_mutex, &input.args.start_time);
	if (input.num % 2 == 0)
	{
		philo_think(input);
		better_sleep(input, input.args.eat_time / 10);
	}
	philo_loop(input);
	return (0);
}
