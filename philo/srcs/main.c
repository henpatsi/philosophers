/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 09:47:27 by hpatsi            #+#    #+#             */
/*   Updated: 2024/02/28 13:00:55 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	destroy_forks(t_args *args)
{
	int	i;

	i = 0;
	while (i < args->philo_count)
	{
		pthread_mutex_destroy(&args->forks[i]);
		i++;
	}
	free(args->forks);
	return (1);
}

int	initialize_forks(t_args *args)
{
	int	i;

	args->forks = malloc(args->philo_count * sizeof(pthread_mutex_t));
	if (args->forks == 0)
		return (-1);
	i = 0;
	while (i < args->philo_count)
	{
		pthread_mutex_init(&args->forks[i], NULL);
		i++;
	}
	return (1);
}

int	prepare_args(t_args *args, int argc, char **argv)
{
	if (argc < 5 || argc > 6)
	{
		printf("program takes 4 or 5 arguments\n");
		return (-1);
	}
	args->philo_count = ft_atoi(argv[1]);
	args->die_time = ft_atoi(argv[2]);
	args->eat_time = ft_atoi(argv[3]);
	args->sleep_time = ft_atoi(argv[4]);
	if (argc == 6)
		args->eat_count = ft_atoi(argv[5]);
	else
		args->eat_count = 0;
	if (gettimeofday(&args->start_time, NULL) == -1)
		return (-1);
	if (initialize_forks(args) == -1)
		return (-1);
	return (1);
}

int	main(int argc, char **argv)
{
	t_args	args;
	int		ret;

	if (prepare_args(&args, argc, argv) == -1)
		return (1);
	ret = initialize_threads(&args);
	destroy_forks(&args);
	if (ret == -1)
		return (1);
	return (0);
}
