/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 11:37:38 by hpatsi            #+#    #+#             */
/*   Updated: 2024/03/15 10:12:40 by hpatsi           ###   ########.fr       */
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
	sem_wait(philo.sems.write);
	printf("%ld %d %s\n", ms, philo.num + 1, state_str);
	sem_post(philo.sems.write);
}

int	set_philo_state(t_args args, t_philo *philo, t_state state)
{
	philo->state = state;
	if (get_exit_state(philo->exit_state, philo->sems.exit))
	{
		if (philo->state == EAT)
			put_down_forks(philo);
		return (-1);
	}
	print_state(args, *philo);
	return (1);
}

int	get_exit_state(int	*exit_state, sem_t *exit_sem)
{
	int	state;

	sem_wait(exit_sem);
	state = *exit_state;
	sem_post(exit_sem);
	return (state);
}
