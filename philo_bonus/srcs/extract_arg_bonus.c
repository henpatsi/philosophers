/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_arg_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 10:28:56 by hpatsi            #+#    #+#             */
/*   Updated: 2024/03/15 10:45:20 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int	extract_error(char	*message)
{
	printf("Error: %s\n", message);
	return (-1);
}

int	extract_arg(int	*dst, const char *str)
{
	int	num;
	int	lastnum;

	if (*str == 0)
		return (extract_error("empty arg"));
	num = 0;
	lastnum = 0;
	while (*str != 0)
	{
		if (!ft_isdigit(*str) && *str != '-')
			return (extract_error("arguments should only contain digits"));
		num *= 10;
		num += (*str - '0');
		if (num <= lastnum)
			return (extract_error("argument must be a positive integer"));
		lastnum = num;
		str++;
	}
	if (num == 0)
		return (extract_error("arguments cannot be 0"));
	*dst = num;
	return (1);
}
