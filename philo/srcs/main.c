/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 09:47:27 by hpatsi            #+#    #+#             */
/*   Updated: 2024/03/05 12:21:29 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	free_all(t_args args, t_mutexes mutexes,
		t_philo *philos, t_thread_input *inputs)
{
	destroy_mutex_list(&mutexes.forks, args);
	destroy_mutex_list(&mutexes.philos, args);
	free(philos);
	free(inputs);
}

int	start_threads(t_args args, t_mutexes mutexes,
		t_philo *philos, t_thread_input *inputs)
{
	pthread_t	*threads;
	int			i;

	threads = malloc(args.philo_count * sizeof(pthread_t));
	if (threads == 0)
		return (-1);
	i = 0;
	while (i < args.philo_count)
	{
		pthread_create(&threads[i], NULL, &philo_start, &inputs[i]);
		i++;
	}
	return (monitor_start(args, mutexes.philos, philos, threads));
}

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
	free_all(args, mutexes, philos, inputs);
	if (ret == -1)
		return (1);
	return (0);
}
