/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:49:28 by hpatsi            #+#    #+#             */
/*   Updated: 2024/03/05 13:11:45 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	initialize_mutex_list(t_mutex **dst, t_args args)
{
	int	i;

	*dst = malloc(args.philo_count * sizeof(t_mutex));
	if (*dst == 0)
		return (-1);
	i = 0;
	while (i < args.philo_count)
	{
		pthread_mutex_init(&(*dst)[i], NULL);
		i++;
	}
	return (1);
}

void	destroy_mutex_list(t_mutex **dst, t_args args)
{
	int	i;

	i = 0;
	while (i < args.philo_count)
	{
		pthread_mutex_destroy(&(*dst)[i]);
		i++;
	}
	free(*dst);
}

void	destroy_all_mutex(t_mutexes *mutexes, t_args args)
{
	destroy_mutex_list(&mutexes->forks, args);
	destroy_mutex_list(&mutexes->philos, args);
}
