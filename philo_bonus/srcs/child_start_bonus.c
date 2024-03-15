/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_start_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 13:54:31 by hpatsi            #+#    #+#             */
/*   Updated: 2024/03/15 12:53:41 by hpatsi           ###   ########.fr       */
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
	info->sems.dead = sem_open("/dead", O_RDONLY);
	info->sems.exit = sem_open("/exit", O_RDONLY);
	info->sems.full = sem_open("/full", O_RDONLY);
	info->sems.forks = 0;
	info->sems.write = 0;
	if (info->sems.dead == SEM_FAILED || info->sems.exit == SEM_FAILED
		|| info->sems.full == SEM_FAILED)
	{
		printf("Error: sem open failed\n");
		close_all(&info->sems);
		return (0);
	}
	sem_wait(info->sems.dead);
	sem_post(info->sems.dead);
	sem_wait(info->sems.exit);
	*info->exit_state = 1;
	sem_post(info->sems.exit);
	sem_post(info->sems.full);
	close_all(&info->sems);
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
	if (philo->sems.forks == SEM_FAILED || philo->sems.full == SEM_FAILED
		|| philo->sems.dead == SEM_FAILED || philo->sems.write == SEM_FAILED
		|| philo->sems.exit == SEM_FAILED)
		return (-1);
	return (1);
}

void	close_and_exit(t_philo *philo, char *error_message)
{
	if (error_message)
		printf("Error: %s\n", error_message);
	close_all(&philo->sems);
	if (philo->sems.exit != SEM_FAILED)
		sem_close(philo->sems.exit);
	exit(0);
}

int	child_start(t_args args, int i)
{
	pthread_t		monitor;
	t_monitor_info	monitor_info;
	t_philo			philo;
	int				exit_state;

	exit_state = 0;
	if (prepare_philo(&philo, args, i, &exit_state) == -1)
		close_and_exit(&philo, "sem open failed");
	monitor_info.exit_state = &exit_state;
	if (pthread_create(&monitor, NULL, death_monitor, &monitor_info) == -1)
		close_and_exit(&philo, "thread create failed");
	set_philo_state(args, &philo, THINK);
	child_loop(args, &philo);
	pthread_join(monitor, NULL);
	close_and_exit(&philo, 0);
	exit (0);
}
