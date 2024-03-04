/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 09:47:27 by hpatsi            #+#    #+#             */
/*   Updated: 2024/03/04 15:21:48 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

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
	if (prepare_philosophers(&philos, args) == -1)
		return (1);
	start_processes(args, forks, philos);
	sem_close(forks);
	free(philos);
	return (0);
}
