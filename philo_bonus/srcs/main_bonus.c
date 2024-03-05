/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 09:47:27 by hpatsi            #+#    #+#             */
/*   Updated: 2024/03/05 15:57:39 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

long	get_time_passed(t_timeval start_time)
{
	t_timeval	time;
	long		ms;

	if (gettimeofday(&time, NULL) == -1)
		return (-1);
	ms = (time.tv_sec - start_time.tv_sec) * 1000;
	ms += (time.tv_usec - start_time.tv_usec) / 1000;
	return (ms);
}

int	main(int argc, char **argv)
{
	t_args	args;
	t_philo	*philos;
	sem_t	*forks;

	if (prepare_args(&args, argc, argv) == -1)
		return (1);
	forks = sem_open("forks", O_CREAT, S_IRWXU, args.philo_count);
	if (forks == SEM_FAILED)
		return (1);
	if (prepare_philosophers(&philos, forks, args) == -1)
		return (1);
	start_processes(args, philos);
	sem_close(forks);
	free(philos);
	return (0);
}
