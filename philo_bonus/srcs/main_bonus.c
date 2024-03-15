/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 09:47:27 by hpatsi            #+#    #+#             */
/*   Updated: 2024/03/15 12:19:11 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	main(int argc, char **argv)
{
	t_args	args;
	t_sems	sems;
	int		ret;

	if (prepare_args(&args, argc, argv) == -1)
		return (1);
	if (prepare_semaphores(&sems, args.philo_count) == -1)
		return (1);
	ret = start_processes(args, sems);
	unlink_all();
	close_all(&sems);
	if (ret == -1)
		return (1);
	return (0);
}
