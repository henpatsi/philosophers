/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 09:47:27 by hpatsi            #+#    #+#             */
/*   Updated: 2024/02/23 10:17:17 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_args(int argc, char **argv)
{
	(void) argv;

	if (argc < 5 || argc > 6)
	{
		printf("program takes 4 or 5 arguments\n");
		return (0);
	}
	else if (argc == 5)
		return (1);
	return (2);
}

int	main(int argc, char **argv)
{
	int mode;
	
	mode = check_args(argc, argv);
	if (mode == 0)
		return (1);
	printf("check = %d", mode);
}
