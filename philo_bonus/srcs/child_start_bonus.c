/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_start_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 13:54:31 by hpatsi            #+#    #+#             */
/*   Updated: 2024/03/15 10:14:04 by hpatsi           ###   ########.fr       */
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
	t_monitor_info	*info;

	info = (t_monitor_info *) arg;
	info->dead_sem = sem_open("/dead", O_RDONLY);
	info->exit_sem = sem_open("/exit", O_RDONLY);
	info->full_sem = sem_open("/full", O_RDONLY);
	sem_wait(info->dead_sem);
	sem_post(info->dead_sem);
	sem_wait(info->exit_sem);
	*info->exit_state = 1;
	sem_post(info->exit_sem);
	sem_post(info->full_sem);
	sem_close(info->dead_sem);
	sem_close(info->exit_sem);
	sem_close(info->full_sem);
	return (0);
}

int	prepare_philo(t_philo *philo, t_args args, int i, int *exit_state)
{
	philo->num = i;
	philo->eat_count = 0;
	philo->exit_state = exit_state;
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
	pthread_t		monitor;
	t_monitor_info	monitor_info;
	t_philo			philo;
	int				exit_state;

	exit_state = 0;
	prepare_philo(&philo, args, i, &exit_state);
	monitor_info.exit_state = &exit_state;
	pthread_create(&monitor, NULL, death_monitor, &monitor_info);
	set_philo_state(args, &philo, THINK);
	child_loop(args, &philo);
	pthread_join(monitor, NULL);
	close_all(&philo.sems);
	sem_close(philo.sems.exit);
	exit (0);
}
