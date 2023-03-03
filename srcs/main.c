/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgiordan <vgiordan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 17:34:09 by vgiordan          #+#    #+#             */
/*   Updated: 2023/03/03 18:26:37 by vgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

static int  parse_args(int argc, char *argv[])
{
	int number_of_philosophers;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;

	if (argc == 5)
	{
		number_of_philosophers = ft_atoi(argv[1]);
		time_to_die = ft_atoi(argv[2]);
		time_to_eat = ft_atoi(argv[3]);
		time_to_sleep = ft_atoi(argv[4]);
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
	return 0;
}
