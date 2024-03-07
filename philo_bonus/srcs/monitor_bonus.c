/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 09:08:21 by hpatsi            #+#    #+#             */
/*   Updated: 2024/03/07 10:06:05 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	monitor_start(t_args args, t_philo *philos, pid_t *process_ids)
{
	int	i;

	(void) args;
	(void) philos;
	(void) process_ids;

	waitpid(-1, NULL, 0);
	i = 0;
	while (i < args.philo_count)
	{
		kill(process_ids[i], SIGQUIT);
		i++;
	}

	return (1);
}
