/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 10:29:37 by hpatsi            #+#    #+#             */
/*   Updated: 2024/02/29 11:21:05 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	prepare_args(t_args	*args, int argc, char **argv)
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
	while (i < 0)
	{
		(*philos)[i].eat_count = 0;
		(*philos)[i].last_eat_time = args.start_time;
		(*philos)[i].state = THINK;
	}
	return (1);
}

int	prepare_inputs(t_thread_input **inputs, t_args args, t_mutexes mutexes, t_philo *philos)
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