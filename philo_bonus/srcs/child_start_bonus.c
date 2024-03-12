/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_start_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 13:54:31 by hpatsi            #+#    #+#             */
/*   Updated: 2024/03/12 09:44:15 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	philo_eat(t_args args, t_philo *philo)
{
	set_philo_state(args, philo, EAT);
	gettimeofday(&philo->last_eat_time, NULL);
	if (better_sleep(args, philo, args.eat_time) == -1)
		return (-1);
	put_down_forks(philo);
	philo->eat_count++;
	if (philo->eat_count == args.eat_count)
		sem_post(philo->sems.full);
	return (1);
}

int	philo_sleep(t_args args, t_philo *philo)
{
	set_philo_state(args, philo, SLEEP);
	if (better_sleep(args, philo, args.sleep_time) == -1)
		return (-1);
	return (1);
}

void	child_loop(t_args args, t_philo *philo)
{
	while (1)
	{
		if (pick_up_forks(args, philo) == -1)
			break ;
		if (philo_eat(args, philo) == -1)
			break ;
		if (philo_sleep(args, philo) == -1)
			break ;
		set_philo_state(args, philo, THINK);
	}
}

int	child_start(t_args args, t_philo *philo)
{
	philo->sems.forks = sem_open("/forks", O_RDONLY);
	philo->sems.full = sem_open("/full", O_RDONLY);
	philo->sems.write = sem_open("/write", O_RDONLY);
	set_philo_state(args, philo, THINK);
	child_loop(args, philo);
	return (1);
}
