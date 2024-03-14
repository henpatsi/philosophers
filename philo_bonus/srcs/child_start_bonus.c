/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_start_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 13:54:31 by hpatsi            #+#    #+#             */
/*   Updated: 2024/03/14 13:51:29 by hpatsi           ###   ########.fr       */
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
		if (philo_sleep(args, philo) == -1 || get_exit_state(philo))
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
	set_exit_state(philo);
	sem_post(philo->sems.full);
	return (0);
}

int	prepare_philo(t_philo *philo, t_args args, int i)
{
	philo->num = i;
	philo->eat_count = 0;
	philo->exit = 0;
	philo->last_eat_time.tv_sec = args.start_time.tv_sec;
	philo->last_eat_time.tv_usec = args.start_time.tv_usec;
	philo->sems.forks = sem_open("/forks", O_RDONLY);
	philo->sems.full = sem_open("/full", O_RDONLY);
	philo->sems.dead = sem_open("/dead", O_RDONLY);
	philo->sems.write = sem_open("/write", O_RDONLY);
	sem_unlink("/exit");
	philo->sems.exit = sem_open("/exit", O_CREAT, 0644, 1);
	return (1);
}

int	child_start(t_args args, int i)
{
	pthread_t	monitor;
	t_philo		philo;

	prepare_philo(&philo, args, i);
	pthread_create(&monitor, NULL, death_monitor, &philo);
	set_philo_state(args, &philo, THINK);
	child_loop(args, &philo);
	pthread_join(monitor, NULL);
	close_all(&philo.sems);
	sem_close(philo.sems.exit);
	exit (0);
}
