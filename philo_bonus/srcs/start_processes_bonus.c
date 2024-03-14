/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_processes_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 10:43:28 by hpatsi            #+#    #+#             */
/*   Updated: 2024/03/14 13:31:33 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	create_child(t_args args, int i, t_sems sems, pid_t	*process_ids)
{
	pid_t	process_id;

	process_id = fork();
	if (process_id == -1)
	{
		printf("fork %d failed\n", i);
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
	sem_t	*full_sem;
	sem_t	*dead_sem;
	sem_t	*write_sem;

	philo_count = *(int *) arg;
	full_sem = sem_open("/full", O_RDONLY);
	dead_sem = sem_open("/dead", O_RDONLY);
	write_sem = sem_open("/write", O_RDONLY);
	i = 0;
	while (i < philo_count)
	{
		sem_wait(full_sem);
		i++;
	}
	sem_post(dead_sem);
	sem_close(full_sem);
	sem_close(dead_sem);
	sem_close(write_sem);
	return (0);
}

int	monitor_start(t_args args, pid_t *process_ids)
{
	int			i;
	pthread_t	monitor;

	pthread_create(&monitor, NULL, full_monitor, &args.philo_count);
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
			free(process_ids);
			return (-1);
		}
		i++;
	}
	ret = monitor_start(args, process_ids);
	free(process_ids);
	return (ret);
}
