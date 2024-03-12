/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 09:47:27 by hpatsi            #+#    #+#             */
/*   Updated: 2024/03/12 13:56:37 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	free_all(t_philo *philos, t_sems *sems)
{
	sem_unlink("/forks");
	sem_unlink("/full");
	sem_unlink("/all_full");
	sem_unlink("/dead");
	sem_unlink("/write");
	sem_close(sems->forks);
	sem_close(sems->full);
	sem_close(sems->all_full);
	sem_close(sems->dead);
	sem_close(sems->write);
	free(philos);
}

int	main(int argc, char **argv)
{
	t_args	args;
	t_philo	*philos;
	t_sems	sems;
	int		ret;

	if (prepare_args(&args, argc, argv) == -1)
		return (1);
	if (prepare_philosophers(&philos, args) == -1)
		return (1);
	if (prepare_semaphores(&sems, args.philo_count) == -1)
	{
		free(philos);
		return (1);
	}
	ret = start_processes(args, philos);
	free_all(philos, &sems);
	if (ret == -1)
		return (1);
	return (0);
}
