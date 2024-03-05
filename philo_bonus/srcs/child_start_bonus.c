/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_start_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 13:54:31 by hpatsi            #+#    #+#             */
/*   Updated: 2024/03/05 16:06:07 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	child_loop(t_args args, t_philo *philo)
{
	while (1)
	{
		// if (pick_up_forks(input) == -1)
		// 	break ;
		// if (philo_eat(input) == -1)
		// 	break ;
		// if (philo_sleep(input) == -1)
		// 	break ;
		// philo_think(input);
	}
}

int	child_start(t_args args, t_philo *philo)
{
	printf("%lu child %d created\n", get_time_passed(args.start_time), philo->num);
	if (philo->num % 2 == 0)
	{
		set_philo_state(args, philo, THINK);
		usleep(args.eat_time / 2);
	}
	child_loop(args, philo);
	return (1);
}
