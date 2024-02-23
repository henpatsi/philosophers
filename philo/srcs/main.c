/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 09:47:27 by hpatsi            #+#    #+#             */
/*   Updated: 2024/02/23 11:54:43 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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
	return (1);
}

void	*counter(void *arg)
{
	t_philo			philo;
	struct timeval	start_time;
	long			ms;
	long			last_ms;

	philo = *(t_philo *) arg;
	if (gettimeofday(&start_time, NULL) == -1)
		return (0);
	last_ms = 0;
	while (1)
	{
		ms = get_time_passed(start_time);
		if (ms - last_ms >= 1000)
		{
			printf("%d: %lu\n", philo.num, ms);
			last_ms = ms;
		}
	}
}

int	main(int argc, char **argv)
{
	t_args	args;
	
	if (prepare_args(&args, argc, argv) == -1)
		return (1);

	t_philo		*philos;
	pthread_t	*threads;
	int			i;

	philos = malloc(args.philo_count * sizeof(philos));
	threads = malloc(args.philo_count * sizeof(pthread_t));
	
	i = 0;
	while (i < args.philo_count)
	{
		philos[i].num = i;
		philos[i].args = args;
		pthread_create(&threads[i], NULL, &counter, &philos[i]);
		i++;
	}
	
	i = 0;
	while (i < args.philo_count)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
}
