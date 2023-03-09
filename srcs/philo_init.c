/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgiordan <vgiordan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 19:26:04 by vgiordan          #+#    #+#             */
/*   Updated: 2023/03/09 18:14:40 by vgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

void    init_philosophers(t_data *data)
{
	int i;
	struct timeval current_time;

	data->philo = malloc(sizeof(t_philo) * (data->args->nb_philos));
	i = 0;
	ft_printf("nbphilos %d\n", data->args->nb_philos);

	ft_printf("mutex address 1 %p\n", data->write_mutex);
	while (i < data->args->nb_philos)
	{
		//data->philo[i].write_mutex = data->write_mutex;
		data->philo[i].id = i + 1;
		gettimeofday(&current_time, NULL);
		data->philo[i].init_time = current_time.tv_sec;
		data->philo[i].init_utime = current_time.tv_usec;
		data->philo[i].last_meal_time = current_time.tv_sec - data->philo[i].init_time;
		data->philo[i].meal_count = 0;
		pthread_mutex_init((&data->philo[i].fork_mutex), NULL);
		if (i == 0)
			data->philo[i].left_fork = data->args->nb_philos - 1;
		else
			data->philo[i].left_fork = i - 1;
		if (i == data->args->nb_philos - 1)
		{
			data->philo[i].right_fork = 0;
		}
		else
		{
			data->philo[i].right_fork = i;	
		}
		i++;
	}
	i = 0;
	while (i < data->args->nb_philos)
	{
		if (i == data->args->nb_philos - 1)
		{
			data->philo[i].next_philo = &(data->philo[0]);
		}
		else
			data->philo[i].next_philo = &(data->philo[i + 1]);
		display_status(&(data->philo[i]), "");
		ft_printf("------------\n");
		i++;
	}
}
