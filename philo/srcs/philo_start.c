/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_start.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 09:15:23 by hpatsi            #+#    #+#             */
/*   Updated: 2024/02/29 10:09:10 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	philo_loop(t_philo *philo, t_args args, t_mutexes *mutexes)
{
	while (args.eat_count == 0 || philo->eat_count < args.eat_count)
	{
		if (pick_up_forks(philo, args, mutexes) == -1)
			break ;
		if (philo_eat(philo, args, mutexes) == -1)
			break ;
		if (philo->eat_count == args.eat_count)
			break ;
		if (philo_sleep(philo, args, mutexes) == -1)
			break ;
		philo_think(philo, args, mutexes);
	}
}

void	*philo_start(void *arg)
{
	t_thread_input	*input;
	t_philo			*philo;
	t_args			args;
	t_mutexes		*mutexes;

	input = (t_thread_input *) arg;
	args = input->args;
	philo = input->philo;
	mutexes = &input->mutexes;
	if (philo->num % 2 == 0)
	{
		philo_think(philo, args, mutexes);
		usleep(1000);
	}
	philo_loop(philo, args, mutexes);
	return (0);
}
