/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgiordan <vgiordan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 17:34:09 by vgiordan          #+#    #+#             */
/*   Updated: 2023/03/06 19:13:27 by vgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

void	*process()
{
	return (NULL);
}

static int  parse_args(int argc, char *argv[])
{
	pthread_t	t1;
	pthread_t	t2;
	t_args		a;

	
	if (argc == 5)
	{
		a.nb_philos = ft_atoi(argv[1]);
		a.time_to_die = ft_atoi(argv[2]);
		a.time_to_eat = ft_atoi(argv[3]);
		a.time_to_sleep = ft_atoi(argv[4]);
		init_philosophers(&a);
		pthread_mutex_init(&(a.philos->mutex), NULL);
		pthread_create(&t1, NULL, process, NULL);
		pthread_create(&t2, NULL, process, NULL);
		pthread_join(t2, NULL);
		pthread_join(t1, NULL);
		display_status(a.philos[1], "is sleeping\n");
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
