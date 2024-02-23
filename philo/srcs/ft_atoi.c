/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 10:28:56 by hpatsi            #+#    #+#             */
/*   Updated: 2024/02/23 10:31:25 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isspace(int c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

int	ft_atoi(const char *str)
{
	int	num;
	int	neg;

	while (ft_isspace(*str))
		str++;
	neg = 1;
	if (*str == '-')
	{
		neg = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	num = 0;
	while (*str != 0 && (*str >= '0' && *str <= '9'))
	{
		num *= 10;
		num += (*str - '0');
		str++;
	}
	return (num * neg);
}
