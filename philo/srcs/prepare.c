/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 10:29:37 by hpatsi            #+#    #+#             */
/*   Updated: 2024/03/04 10:27:39 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_arg_count(int argc)
{
	if (argc < 5 || argc > 6)
	{
		printf("Error: program takes 4 or 5 arguments\n");
		return (-1);
	}
	return (1);
}

int	prepare_args(t_args	*args, int argc, char **argv)
{
	if (check_arg_count(argc) == -1)
		return (-1);
	if (extract_arg(&args->philo_count, argv[1]) == -1)
		return (-1);
	if (extract_arg(&args->die_time, argv[2]) == -1)
		return (-1);
	if (extract_arg(&args->eat_time, argv[3]) == -1)
		return (-1);
	if (extract_arg(&args->sleep_time, argv[4]) == -1)
		return (-1);
	if (argc == 6)
	{
		if (extract_arg(&args->eat_count, argv[5]) == -1)
			return (-1);
	}
	else
		args->eat_count = 0;
	if (gettimeofday(&args->start_time, NULL) == -1)
		return (-1);
	return (1);
}

int	prepare_mutexes(t_mutexes *mutexes, t_args args)
{
	if (initialize_mutex_list(&mutexes->forks, args) == -1)
		return (-1);
	if (initialize_mutex_list(&mutexes->philos, args) == -1)
	{
		destroy_mutex_list(&mutexes->forks, args);
		return (-1);
	}
	return (1);
}

int	prepare_philosophers(t_philo **philos, t_args args)
{
	int	i;

	*philos = malloc(args.philo_count * sizeof(t_philo));
	if (*philos == 0)
		return (-1);
	i = 0;
	while (i < args.philo_count)
	{
		(*philos)[i].eat_count = 0;
		(*philos)[i].state = THINK;
		(*philos)[i].exiting = 0;
		(*philos)[i].last_eat_time.tv_sec = args.start_time.tv_sec;
		(*philos)[i].last_eat_time.tv_usec = args.start_time.tv_usec;
		i++;
	}
	return (1);
}

int	prepare_inputs(t_thread_input **inputs, t_args args,
		t_mutexes mutexes, t_philo *philos)
{
	int	i;

	*inputs = malloc(args.philo_count * sizeof(t_thread_input));
	if (*inputs == 0)
		return (-1);
	i = 0;
	while (i < args.philo_count)
	{
		(*inputs)[i].num = i;
		(*inputs)[i].philo = &philos[i];
		(*inputs)[i].args = args;
		(*inputs)[i].philo_mutex = &mutexes.philos[i];
		if (i == 0)
			(*inputs)[i].left_fork = &mutexes.forks[args.philo_count - 1];
		else
			(*inputs)[i].left_fork = &mutexes.forks[i - 1];
		(*inputs)[i].right_fork = &mutexes.forks[i];
		i++;
	}
	return (1);
}
