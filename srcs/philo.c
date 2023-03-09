/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgiordan <vgiordan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 14:54:09 by vgiordan          #+#    #+#             */
/*   Updated: 2023/03/09 16:50:12 by vgiordan         ###   ########.fr       */
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
		pthread_mutex_lock(&(p->write_mutex));
		ft_printf("Philosophers %d %p\n", p->id, p->write_mutex);
		pthread_mutex_unlock(&(p->write_mutex));
		//take_fork(p);
		
		total++;
		if (total > 10)
		{
			total = 0;
			break;
		}
		
	}
    return (NULL);
}

void process(t_data *data)
{
	int			i;

	i = 0;
	init_philosophers(data);
	while (i < data->args->nb_philos)
	{
		if ((pthread_create(&(data->philo[i].thread), NULL, philo_routine, &(data->philo[i]))) != 0)
			exit(1);
		i++;
	}
	i = 0;
	while (i < data->args->nb_philos)
	{
		if ((pthread_join(data->philo[i].thread, NULL)) != 0)
			exit(1);
		i++;
	}
	free(data->philo);
}