/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_processes_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 10:43:28 by hpatsi            #+#    #+#             */
/*   Updated: 2024/03/04 15:26:28 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	start_child(t_args args, sem_t *forks, t_philo *philos, int i)
{
	pid_t	process_id;
	(void) args;
	(void) forks;
	(void) philos;

	process_id = fork();
	if (process_id == -1)
	{
		printf("fork %d failed\n", i);
		return (-1);
	}
	if (process_id == 0)
	{
		printf("child %d created\n", i);
		exit(0);
	}
	return (process_id);
}

int	start_processes(t_args args, sem_t *forks, t_philo *philos)
{
	pid_t	*process_ids;
	int		i;

	process_ids = malloc(args.philo_count * sizeof(pid_t));
	if (process_ids == 0)
		return (-1);
	i = 0;
	while (i < args.philo_count)
	{
		process_ids[i] = start_child(args, forks, philos, i);
		i++;
	}
	//return (monitor_start(args, mutexes.philos, philos, threads));
	free(process_ids);
	return (1);
}
