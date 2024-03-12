/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_start_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 13:54:31 by hpatsi            #+#    #+#             */
/*   Updated: 2024/03/12 14:02:24 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

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

void	*death_monitor(void *arg)
{
	sem_t	*dead_sem;

	(void) arg;
	dead_sem = sem_open("/dead", O_RDONLY);
	sem_wait(dead_sem);
	sem_post(dead_sem);
	exit (0);
}

void	*all_full_monitor(void	*arg)
{
	sem_t	*all_full_sem;

	(void) arg;
	all_full_sem = sem_open("/all_full", O_RDONLY);
	sem_wait(all_full_sem);
	sem_post(all_full_sem);
	exit (0);
}

int	child_start(t_args args, t_philo *philo)
{
	pthread_t	monitor1;
	pthread_t	monitor2;

	pthread_create(&monitor1, NULL, death_monitor, NULL);
	pthread_create(&monitor2, NULL, all_full_monitor, NULL);
	philo->sems.forks = sem_open("/forks", O_RDONLY);
	philo->sems.full = sem_open("/full", O_RDONLY);
	philo->sems.dead = sem_open("/dead", O_RDONLY);
	philo->sems.write = sem_open("/write", O_RDONLY);
	set_philo_state(args, philo, THINK);
	child_loop(args, philo);
	return (1);
}
