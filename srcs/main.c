/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgiordan <vgiordan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 17:34:09 by vgiordan          #+#    #+#             */
/*   Updated: 2023/03/08 17:27:51 by vgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

static int  parse_args(int argc, char *argv[])
{

	t_args		args;
	int			i;

	i = 0;
	if (argc == 5 || argc == 6)
	{
		args.nb_philos = ft_atoi(argv[1]);
		args.time_to_die = ft_atoi(argv[2]);
		args.time_to_eat = ft_atoi(argv[3]);
		args.time_to_sleep = ft_atoi(argv[4]);
		if (argc == 6)
			args.max_eat -= ft_atoi(argv[5]);
		process(&args);
		return (1);
	}
	
	else
		return (0);
}

int	main(int argc, char *argv[])
{
	if (parse_args(argc, argv) == 0)
	{
		ft_putstr_fd("usage ./philo <> <> <> <>\n", 1);
		return (0);
	}
	else
	{
		
	}
	return 0;
}
