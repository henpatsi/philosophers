/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_start.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 09:15:23 by hpatsi            #+#    #+#             */
/*   Updated: 2024/02/29 11:21:46 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	philo_loop(t_thread_input input)
{
	while (input.args.eat_count == 0 || input.philo->eat_count < input.args.eat_count)
	{
		if (pick_up_forks(input) == -1)
			break ;
		if (philo_eat(input) == -1)
			break ;
		if (input.philo->eat_count == input.args.eat_count)
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
	if (input.num % 2 == 0)
	{
		philo_think(input);
		usleep(1000);
	}
	philo_loop(input);
	return (0);
}
