/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 10:29:37 by hpatsi            #+#    #+#             */
/*   Updated: 2024/03/15 12:12:24 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	prepare_args(t_args	*args, int argc, char **argv)
{
	if (argc < 5 || argc > 6)
	{
		printf("Error: program takes 4 or 5 arguments\n");
		return (-1);
	}
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
		destroy_mutex_list(&mutexes->forks, args.philo_count);
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
		(*philos)[i].exiting = 0;
		(*philos)[i].last_eat_time.tv_sec = args.start_time.tv_sec;
		(*philos)[i].last_eat_time.tv_usec = args.start_time.tv_usec;
		i++;
	}
	return (1);
}

void	set_forks(t_thread_input *input, t_args args,
		t_mutexes mutexes, int i)
{
	if (i % 2 == 0)
	{
		if (i == 0)
			input->left_fork = &mutexes.forks[args.philo_count - 1];
		else
			input->left_fork = &mutexes.forks[i - 1];
		input->right_fork = &mutexes.forks[i];
	}
	else
	{
		input->right_fork = &mutexes.forks[i - 1];
		input->left_fork = &mutexes.forks[i];
	}
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
		(*inputs)[i].state = THINK;
		(*inputs)[i].philo = &philos[i];
		(*inputs)[i].args = args;
		(*inputs)[i].philo_mutex = &mutexes.philos[i];
		set_forks(&(*inputs)[i], args, mutexes, i);
		i++;
	}
	return (1);
}
