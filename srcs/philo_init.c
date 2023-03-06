/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgiordan <vgiordan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 19:26:04 by vgiordan          #+#    #+#             */
/*   Updated: 2023/03/06 19:42:52 by vgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

void    init_philosophers(t_args *args)
{
	int i;
	t_philo *p;
	p = malloc(sizeof(t_philo) * args->nb_philos);
	i = 0;
	while (i < args->nb_philos)
	{
		p[i].id = i + 1;
		p[i].args = args;
		p[i].last_meal_time = gettimeofday(1, 1);
		p[i].meals_eaten = 0;
		if (pthread_mutex_init(&p[i].fork_mutex, NULL) != 0)
			exit(1);
		if (i == 0)
			p[i].left_fork = args->nb_philos - 1;
		else
			p[i].left_fork = i - 1;
		p[i].right_fork = i;
		i++;
	}
	args->philos = p;
}