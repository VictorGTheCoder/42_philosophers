/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgiordan <vgiordan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 14:54:09 by vgiordan          #+#    #+#             */
/*   Updated: 2023/03/14 10:24:36 by vgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

pthread_mutex_t mutex;

void *monitor_philos(void *p)
{
    t_data *data;
    int i;

    data = (t_data *)p;
    while (1)
    {
        i = 0;
        while (i < data->args->nb_philos)
        {
            philo_is_dead(&data->philo[i]);
            i++;
        }
        usleep(1000);
    }
}

void *philo_routine(void *p)
{
    t_philo *philo;

    philo = (t_philo *)p;
    while (philo->args->max_eat > 0 && philo->meal_count < philo->args->max_eat)
    {
		if (philo->status == DEAD)
			exit(1);
        take_fork(philo);
    }
	philo->status = DEAD;
	printf("\x1B[33m%lldms  Philo %d has eaten %d times on %d\n", ft_time() - philo->init_time, philo->id, philo->meal_count, philo->args->max_eat);
    return (NULL);
}

void process(t_data *data)
{
	int			i;
	pthread_t monitor_thread;

	i = 0;
	init_philosophers(data);
	if (pthread_create(&monitor_thread, NULL, monitor_philos, data) != 0)
		exit(1);

	while (i < data->args->nb_philos)
	{
		if ((pthread_create(&(data->philo[i].thread), NULL, philo_routine, (&data->philo[i]))) != 0)
		{
			perror("thread");
			exit(1);
		}
		i++;
	}
	i = 0;
	while (i < data->args->nb_philos)
	{
		if ((pthread_join(data->philo[i].thread, NULL)) != 0)
		{
			perror("thread");
			exit(1);
		}
		i++;
	}
	pthread_mutex_destroy(&(data->write_mutex));
	free(data->philo);
}
