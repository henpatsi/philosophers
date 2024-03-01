/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 09:47:27 by hpatsi            #+#    #+#             */
/*   Updated: 2024/03/01 12:30:22 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_args			args;
	t_mutexes		mutexes;
	t_philo			*philos;
	t_thread_input	*inputs;
	int				ret;

	if (prepare_args(&args, argc, argv) == -1)
		return (1);
	if (prepare_mutexes(&mutexes, args) == -1)
		return (1);
	if (prepare_philosophers(&philos, args) == -1)
		return (1);
	if (prepare_inputs(&inputs, args, mutexes, philos) == -1)
	{
		free(philos);
		return (1);
	}
	ret = start_threads(args, mutexes, philos, inputs);
	destroy_mutex_list(&mutexes.forks, args);
	destroy_mutex_list(&mutexes.philos, args);
	free(philos);
	free(inputs);
	if (ret == -1)
		return (1);
	return (0);
}
