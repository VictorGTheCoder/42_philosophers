/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgiordan <vgiordan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 19:26:04 by vgiordan          #+#    #+#             */
/*   Updated: 2023/03/09 15:54:56 by vgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

void    init_philosophers(t_args *args, t_philo **p)
{
	int i;
	struct timeval current_time;

	*p = malloc(sizeof(t_philo) * (args->nb_philos));
	i = 0;
	ft_printf("nbphilos %d\n", args->nb_philos);
	pthread_mutex_init((&(*p)[0].write_mutex), NULL);
	while (i < args->nb_philos)
	{
		(*p)[i].id = i + 1;
		//(*p)[i].args = args;
		gettimeofday(&current_time, NULL);
		(*p)[i].init_time = current_time.tv_sec;
		(*p)[i].init_utime = current_time.tv_usec;
		(*p)[i].last_meal_time = current_time.tv_sec - (*p)[i].init_time;
		(*p)[i].meal_count = 0;
		if (i != 0)
		{
			((*p)[i].write_mutex) = ((*p)[0].write_mutex); 
		}
		pthread_mutex_init((&(*p)[i].fork_mutex), NULL);
		if (i == 0)
			(*p)[i].left_fork = args->nb_philos - 1;
		else
			(*p)[i].left_fork = i - 1;
		if (i == args->nb_philos - 1)
		{
			(*p)[i].right_fork = 0;
		}
		else
		{
			(*p)[i].right_fork = i;	
		}
		i++;
	}
	i = 0;
	while (i < args->nb_philos)
	{
		if (i == args->nb_philos - 1)
		{
			(*p)[i].next_philo = &((*p)[0]);
		}
		else
			(*p)[i].next_philo = &((*p)[i + 1]);
		display_status(&((*p)[i]), "");
		ft_printf("------------\n");
		i++;
	}
}
