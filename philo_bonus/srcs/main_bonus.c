/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 09:47:27 by hpatsi            #+#    #+#             */
/*   Updated: 2024/03/07 11:54:46 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	free_all(t_philo *philos, sem_t *forks, sem_t *full)
{
	sem_unlink("/forks");
	sem_unlink("/full");
	sem_close(forks);
	sem_close(full);
	free(philos);
}

int	main(int argc, char **argv)
{
	t_args	args;
	t_philo	*philos;
	sem_t	*forks;
	sem_t	*full;
	int		ret;

	if (prepare_args(&args, argc, argv) == -1)
		return (1);
	if (prepare_philosophers(&philos, args) == -1)
		return (1);
	if (prepare_semaphores(&forks, &full, args.philo_count) == -1)
	{
		free(philos);
		return (1);
	}
	ret = start_processes(args, philos, full);
	free_all(philos, forks, full);
	if (ret == -1)
		return (1);
	return (0);
}
