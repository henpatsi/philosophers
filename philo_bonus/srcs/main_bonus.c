/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 09:47:27 by hpatsi            #+#    #+#             */
/*   Updated: 2024/03/07 10:18:13 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	main(int argc, char **argv)
{
	t_args	args;
	t_philo	*philos;
	sem_t	*forks;
	int		ret;

	if (prepare_args(&args, argc, argv) == -1)
		return (1);
	if (prepare_philosophers(&philos, args) == -1)
		return (1);
	if (prepare_forks(&forks, args.philo_count) == -1)
	{
		free(philos);
		return (1);
	}
	ret = start_processes(args, philos);
	sem_unlink("/forks");
	sem_close(forks);
	free(philos);
	if (ret == -1)
		return (1);
	return (0);
}
