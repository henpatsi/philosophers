/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 09:47:27 by hpatsi            #+#    #+#             */
/*   Updated: 2024/03/13 10:18:31 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	unlink_all(void)
{
	sem_unlink("/forks");
	sem_unlink("/full");
	sem_unlink("/dead");
	sem_unlink("/write");
}

void	close_all(t_sems *sems)
{
	if (sems->forks != 0)
		sem_close(sems->forks);
	if (sems->full != 0)
		sem_close(sems->full);
	if (sems->dead != 0)
		sem_close(sems->dead);
	if (sems->write != 0)
		sem_close(sems->write);
}

int	main(int argc, char **argv)
{
	t_args	args;
	t_sems	sems;
	int		ret;

	if (prepare_args(&args, argc, argv) == -1)
		return (1);
	if (prepare_semaphores(&sems, args.philo_count) == -1)
		return (1);
	ret = start_processes(args);
	unlink_all();
	close_all(&sems);
	if (ret == -1)
		return (1);
	return (0);
}
