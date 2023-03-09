/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgiordan <vgiordan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 14:54:09 by vgiordan          #+#    #+#             */
/*   Updated: 2023/03/09 18:42:06 by vgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

pthread_mutex_t mutex;

void    *philo_routine(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	while (42)
	{
		pthread_mutex_lock(philo->write_mutexcpy);
		ft_printf("Philo %d mutex address %p\n", philo->id, philo->write_mutexcpy);
		pthread_mutex_unlock(philo->write_mutexcpy);
		usleep(50000);
	}
    return (NULL);
}

void process(t_data *data)
{
	int			i;

	i = 0;
	//pthread_mutex_init(&mutex, NULL);
	init_philosophers(data);
	//ft_printf("mutex address 2 %p\n", &data->write_mutex);
	while (i < data->args->nb_philos)
	{
		if ((pthread_create(&(data->philo[i].thread), NULL, philo_routine, (&data->philo[i]))) != 0)
			exit(1);
		ft_printf("Thread %d create\n", i);
		sleep(1);
		i++;
	}
	i = 0;
	while (i < data->args->nb_philos)
	{
		if ((pthread_join(data->philo[i].thread, NULL)) != 0)
			exit(1);
		i++;
	}
	pthread_mutex_destroy(&(data->write_mutex));
	free(data->philo);
}