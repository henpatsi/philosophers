/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_processes_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 10:43:28 by hpatsi            #+#    #+#             */
/*   Updated: 2024/03/07 12:53:48 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	create_child(t_args args, t_philo *philos, int i)
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
		child_start(args, &philos[i]);
		return (-1);
	}
	return (process_id);
}

int	start_processes(t_args args, t_philo *philos, t_sems *sems)
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
		process_ids[i] = create_child(args, philos, i);
		if (process_ids[i] == -1)
		{
			free(process_ids);
			return (-1);
		}
		i++;
	}
	ret = monitor_start(args, process_ids, sems);
	free(process_ids);
	return (ret);
}
