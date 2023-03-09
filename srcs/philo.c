/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgiordan <vgiordan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 14:54:09 by vgiordan          #+#    #+#             */
/*   Updated: 2023/03/09 15:10:28 by vgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int total = 0;
void    *philo_routine(void *philo)
{
	t_philo *p;

	p = philo;
	while (42)
	{
		take_fork(p);
		
		total++;
		if (total > 10)
		{
			total = 0;
			break;
		}
		
	}
    return (NULL);
}

void process(t_args *args)
{
	t_philo		*philo;
	int			i;

	i = 0;
	init_philosophers(args, &philo);
	while (i < philo->args->nb_philos)
	{
		if ((pthread_create(&(philo[i].thread), NULL, philo_routine, &(philo[i]))) != 0)
			exit(1);
		i++;
	}
	i = 0;
	while (i < philo->args->nb_philos)
	{
		if ((pthread_join(philo[i].thread, NULL)) != 0)
			exit(1);
		i++;
	}
	free(philo);
}