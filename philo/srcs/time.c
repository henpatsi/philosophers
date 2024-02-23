/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 10:57:37 by hpatsi            #+#    #+#             */
/*   Updated: 2024/02/23 11:24:47 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	get_time_passed(struct timeval start_time)
{
	struct timeval	time;
	long			ms;

	if (gettimeofday(&time, NULL) == -1)
		return (-1);
	ms = (time.tv_sec - start_time.tv_sec) * 1000;
	ms += (time.tv_usec - start_time.tv_usec) / 1000;
	return (ms);
}
