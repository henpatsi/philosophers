/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 10:29:37 by hpatsi            #+#    #+#             */
/*   Updated: 2024/03/18 12:23:18 by hpatsi           ###   ########.fr       */
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

void	unlink_all(void)
{
	sem_unlink("/forks");
	sem_unlink("/full");
	sem_unlink("/dead");
	sem_unlink("/write");
	sem_unlink("/exit");
}

void	close_all(t_sems *sems)
{
	if (sems->forks != 0 && sems->forks != SEM_FAILED)
		sem_close(sems->forks);
	if (sems->full != 0 && sems->full != SEM_FAILED)
		sem_close(sems->full);
	if (sems->dead != 0 && sems->dead != SEM_FAILED)
		sem_close(sems->dead);
	if (sems->write != 0 && sems->write != SEM_FAILED)
		sem_close(sems->write);
}

int	sem_error(t_sems *sems)
{
	printf("Error: failed to open semaphore");
	unlink_all();
	close_all(sems);
	return (-1);
}

int	prepare_semaphores(t_sems *sems, int count)
{
	sems->forks = 0;
	sems->full = 0;
	sems->dead = 0;
	sems->write = 0;
	unlink_all();
	sems->forks = sem_open("/forks", O_CREAT, 0644, count);
	if (sems->forks == SEM_FAILED)
		return (sem_error(sems));
	sems->full = sem_open("/full", O_CREAT, 0644, 0);
	if (sems->full == SEM_FAILED)
		return (sem_error(sems));
	sems->dead = sem_open("/dead", O_CREAT, 0644, 0);
	if (sems->dead == SEM_FAILED)
		return (sem_error(sems));
	sems->write = sem_open("/write", O_CREAT, 0644, 1);
	if (sems->write == SEM_FAILED)
		return (sem_error(sems));
	return (1);
}
