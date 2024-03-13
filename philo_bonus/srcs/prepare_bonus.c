/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 10:29:37 by hpatsi            #+#    #+#             */
/*   Updated: 2024/03/12 14:53:52 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	prepare_args(t_args	*args, int argc, char **argv)
{
	if (argc < 5 || argc > 6)
	{
		printf("Error: program takes 4 or 5 arguments\n");
		return (-1);
	}
	if (extract_arg(&args->philo_count, argv[1]) == -1)
		return (-1);
	if (extract_arg(&args->die_time, argv[2]) == -1)
		return (-1);
	if (extract_arg(&args->eat_time, argv[3]) == -1)
		return (-1);
	if (extract_arg(&args->sleep_time, argv[4]) == -1)
		return (-1);
	if (argc == 6)
	{
		if (extract_arg(&args->eat_count, argv[5]) == -1)
			return (-1);
	}
	else
		args->eat_count = 0;
	if (gettimeofday(&args->start_time, NULL) == -1)
		return (-1);
	return (1);
}

int	prepare_philosophers(t_philo **philos, t_args args)
{
	int	i;

	*philos = malloc(args.philo_count * sizeof(t_philo));
	if (*philos == 0)
		return (-1);
	i = 0;
	while (i < args.philo_count)
	{
		(*philos)[i].num = i;
		(*philos)[i].eat_count = 0;
		(*philos)[i].state = THINK;
		(*philos)[i].last_eat_time.tv_sec = args.start_time.tv_sec;
		(*philos)[i].last_eat_time.tv_usec = args.start_time.tv_usec;
		i++;
	}
	return (1);
}

int	sem_error(t_sems *sems)
{
	printf("Error: failed to open semaphore");
	sem_unlink("/forks");
	sem_unlink("/full");
	sem_unlink("/dead");
	sem_unlink("/write");
	if (sems->forks != 0)
		sem_close(sems->forks);
	if (sems->full != 0)
		sem_close(sems->full);
	if (sems->dead != 0)
		sem_close(sems->dead);
	if (sems->write != 0)
		sem_close(sems->write);
	return (-1);
}

int	prepare_semaphores(t_sems *sems, int count)
{
	sem_unlink("/forks");
	sems->forks = sem_open("/forks", O_CREAT, 0644, count);
	if (sems->forks == SEM_FAILED)
		return (sem_error(sems));
	sem_unlink("/full");
	sems->full = sem_open("/full", O_CREAT, 0644, 0);
	if (sems->full == SEM_FAILED)
		return (sem_error(sems));
	sem_unlink("/dead");
	sems->dead = sem_open("/dead", O_CREAT, 0644, 0);
	if (sems->dead == SEM_FAILED)
		return (sem_error(sems));
	sem_unlink("/write");
	sems->write = sem_open("/write", O_CREAT, 0644, 1);
	if (sems->write == SEM_FAILED)
		return (sem_error(sems));
	return (1);
}
