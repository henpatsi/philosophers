/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_philo_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 11:37:38 by hpatsi            #+#    #+#             */
/*   Updated: 2024/03/05 16:05:11 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	print_state(t_args args, t_philo philo)
{
	long	ms;
	char	*state_str;

	ms = get_time_passed(args.start_time);
	if (ms == -1)
		return ;
	if (philo.state == EAT)
		state_str = "is eating";
	else if (philo.state == SLEEP)
		state_str = "is sleeping";
	else if (philo.state == THINK)
		state_str = "is thinking";
	else
		state_str = "";
	printf("%ld %d %s\n", ms, philo.num + 1, state_str);
}

int	set_philo_state(t_args args, t_philo *philo, t_state state)
{
	philo->state = state;
	print_state(args, *philo);
	return (1);
}
