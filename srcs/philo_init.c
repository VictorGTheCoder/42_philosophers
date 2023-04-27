/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgiordan <vgiordan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 19:26:04 by vgiordan          #+#    #+#             */
/*   Updated: 2023/04/27 17:48:21 by vgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

void	init_philosophers(t_data *data)
{
	int	i;

	data->philo = malloc(sizeof(t_philo) * (data->args->nb_philos));
	i = -1;
	while (++i < data->args->nb_philos)
	{
		data->philo[i].status = SLEEPTHINK;
		data->philo[i].args = data->args;
		data->philo[i].id = i;
		data->philo[i].init_time = ft_time();
		data->philo[i].last_meal_time = ft_time();
		data->philo[i].meal_count = 0;
		data->philo[i].can_eat = 0;
		pthread_mutex_init((&data->philo[i].fork_mutex), NULL);
	}
	i = -1;
	while (++i < data->args->nb_philos)
	{
		if (i == data->args->nb_philos - 1)
			data->philo[i].next_philo = &(data->philo[0]);
		else
			data->philo[i].next_philo = &(data->philo[i + 1]);
	}
}
