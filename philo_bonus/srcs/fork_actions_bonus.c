/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_actions_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 14:49:10 by hpatsi            #+#    #+#             */
/*   Updated: 2024/03/14 17:39:20 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	print_fork(t_args args, t_philo *philo)
{
	long	ms;

	ms = get_time_passed(args.start_time);
	if (ms == -1)
		return (-1);
	sem_wait(philo->sems.write);
	if (!get_exit_state(philo))
		printf("%ld %d %s\n", ms, philo->num + 1, "has taken a fork");
	sem_post(philo->sems.write);
	return (1);
}

int	one_fork_death(t_args args, t_philo *philo)
{
	better_sleep(args, philo, args.die_time * 2);
	sem_post(philo->sems.forks);
	return (-1);
}

int	put_down_forks(t_philo *philo)
{
	sem_post(philo->sems.forks);
	sem_post(philo->sems.forks);
	return (1);
}

int	has_time_to_eat(t_args args, t_philo *philo)
{
	if (philo->eat_count == 0 && philo->num % 2 != 0)
		better_sleep(args, philo, args.eat_time);
	if (args.philo_count == 1 || args.philo_count % 2 == 0)
		return (1);
	if (get_time_passed(philo->last_eat_time) + args.eat_time > args.die_time)
		return (0);
	return (1);
}

int	pick_up_forks(t_args args, t_philo *philo)
{
	if (!has_time_to_eat(args, philo))
		return (better_sleep(args, philo, args.eat_time));
	sem_wait(philo->sems.forks);
	if (print_fork(args, philo) == -1)
	{
		sem_post(philo->sems.forks);
		return (-1);
	}
	if (args.philo_count == 1)
		return (one_fork_death(args, philo));
	sem_wait(philo->sems.forks);
	if (print_fork(args, philo) == -1)
	{
		put_down_forks(philo);
		return (-1);
	}
	return (1);
}
