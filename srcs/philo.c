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
            if (philo_is_dead(&data->philo[i]))
            {
                pthread_mutex_lock(&data->write_mutex);
                //printf("Philosopher %d has died\n", i + 1);
                pthread_mutex_unlock(&data->write_mutex);
                return (NULL);
            }
            i++;
        }
        usleep(1000);
    }
}

void    *philo_routine(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	while (philo->status != DEAD)
	{
		take_fork(philo);
	}
    return (NULL);
}

void process(t_data *data)
{
	int			i;
	pthread_t monitor_thread;

	i = 0;
	//pthread_mutex_init(&mutex, NULL);
	init_philosophers(data);
	//ft_printf("mutex address 2 %p\n", &data->write_mutex);
	
	if (pthread_create(&monitor_thread, NULL, monitor_philos, data) != 0)
		exit(1);

	while (i < data->args->nb_philos)
	{
		if ((pthread_create(&(data->philo[i].thread), NULL, philo_routine, (&data->philo[i]))) != 0)
			exit(1);
		//ft_printf("Thread %d create\n", i);
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
