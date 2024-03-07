/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 09:08:21 by hpatsi            #+#    #+#             */
/*   Updated: 2024/03/07 12:13:31 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	food_monitor(t_args args, sem_t *full)
{
	int	i;

	i = 0;
	while (i < args.philo_count)
	{
		sem_wait(full);
		i++;
	}
	return (1);
}

int	monitor_start(t_args args, pid_t *process_ids, sem_t *full)
{
	int		i;
	pid_t	food_monitor_id;

	food_monitor_id = fork();
	if (food_monitor_id == -1)
	{
		printf("monitor fork failed\n");
		return (-1);
	}
	if (food_monitor_id == 0)
		return (food_monitor(args, full));
	waitpid(-1, NULL, 0);
	i = 0;
	kill(food_monitor_id, SIGKILL);
	while (i < args.philo_count)
	{
		kill(process_ids[i], SIGKILL);
		i++;
	}
	
	return (1);
}
