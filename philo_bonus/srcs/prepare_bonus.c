/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 10:29:37 by hpatsi            #+#    #+#             */
/*   Updated: 2024/03/13 10:02:50 by hpatsi           ###   ########.fr       */
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

int	sem_error(t_sems *sems)
{
	printf("Error: failed to open semaphore");
	unlink_all();
	close_all(sems);
	return (-1);
}

int	prepare_semaphores(t_sems *sems, int count)
{
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
