/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_processes_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 10:43:28 by hpatsi            #+#    #+#             */
/*   Updated: 2024/03/18 12:23:13 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	create_child(t_args args, int i, t_sems sems, pid_t	*process_ids)
{
	pid_t	process_id;

	process_id = fork();
	if (process_id == -1)
	{
		printf("Error: fork %d failed\n", i);
		return (-1);
	}
	if (process_id == 0)
	{
		close_all(&sems);
		free(process_ids);
		child_start(args, i);
		return (-1);
	}
	return (process_id);
}

void	*full_monitor(void	*arg)
{
	int		i;
	int		philo_count;
	t_sems	sems;

	philo_count = *(int *) arg;
	sems.full = sem_open("/full", O_RDONLY);
	sems.dead = sem_open("/dead", O_RDONLY);
	sems.exit = 0;
	sems.forks = 0;
	sems.write = 0;
	if (sems.full == SEM_FAILED || sems.dead == SEM_FAILED)
	{
		printf("Error: monitor sem open failed\n");
		close_all(&sems);
		return (0);
	}
	i = 0;
	while (i++ < philo_count)
		sem_wait(sems.full);
	sem_post(sems.dead);
	close_all(&sems);
	return (0);
}

int	monitor_start(t_args args, pid_t *process_ids)
{
	int			i;
	pthread_t	monitor;

	if (pthread_create(&monitor, NULL, full_monitor, &args.philo_count) == -1)
	{
		printf("Error: failed to create thread\n");
		return (-1);
	}
	i = 0;
	while (i < args.philo_count)
	{
		waitpid(process_ids[i], NULL, 0);
		i++;
	}
	pthread_join(monitor, NULL);
	return (1);
}

int	start_processes(t_args args, t_sems sems)
{
	pid_t	*process_ids;
	int		i;
	int		ret;

	process_ids = malloc(args.philo_count * sizeof(pid_t));
	if (process_ids == 0)
		return (-1);
	i = 0;
	while (i < args.philo_count)
	{
		process_ids[i] = create_child(args, i, sems, process_ids);
		if (process_ids[i] == -1)
		{
			sem_post(sems.dead);
			free(process_ids);
			return (-1);
		}
		i++;
	}
	ret = monitor_start(args, process_ids);
	if (ret == -1)
		sem_post(sems.dead);
	free(process_ids);
	return (ret);
}
