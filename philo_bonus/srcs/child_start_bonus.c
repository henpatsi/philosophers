/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_start_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 13:54:31 by hpatsi            #+#    #+#             */
/*   Updated: 2024/03/13 16:04:58 by hpatsi           ###   ########.fr       */
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
	t_philo	*philo;

	philo = (t_philo *) arg;
	sem_wait(philo->sems.dead);
	sem_post(philo->sems.dead);
	sem_close(philo->sems.forks);
	sem_close(philo->sems.full);
	sem_close(philo->sems.dead);
	sem_post(philo->sems.write);
	sem_close(philo->sems.write);
	exit (0);
}

int	child_start(t_args args, int i)
{
	pthread_t	monitor;
	t_philo		philo;

	philo.num = i;
	philo.eat_count = 0;
	philo.last_eat_time.tv_sec = args.start_time.tv_sec;
	philo.last_eat_time.tv_usec = args.start_time.tv_usec;
	philo.sems.forks = sem_open("/forks", O_RDONLY);
	philo.sems.full = sem_open("/full", O_RDONLY);
	philo.sems.dead = sem_open("/dead", O_RDONLY);
	philo.sems.write = sem_open("/write", O_RDONLY);
	pthread_create(&monitor, NULL, death_monitor, &philo);
	set_philo_state(args, &philo, THINK);
	child_loop(args, &philo);
	pthread_join(monitor, NULL);
	exit (0);
}
