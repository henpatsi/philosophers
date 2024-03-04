/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_arg_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 10:28:56 by hpatsi            #+#    #+#             */
/*   Updated: 2024/03/04 15:04:19 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	ft_isspace(int c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

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

	if (*str == 0)
		return (extract_error("empty arg"));
	num = 0;
	while (*str != 0 && ft_isdigit(*str))
	{
		num *= 10;
		num += (*str - '0');
		str++;
	}
	if (*str != 0)
		return (extract_error("arguments should only contain digits"));
	if (num == 0)
		return (extract_error("arguments cannot be 0"));
	*dst = num;
	return (1);
}
