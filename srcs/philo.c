/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgiordan <vgiordan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 14:54:09 by vgiordan          #+#    #+#             */
/*   Updated: 2023/04/27 17:49:28 by vgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

void	*monitor_philos(void *p)
{
	t_data	*data;
	int		i;
	int		j;

	data = (t_data *) p;
	i = 0;
	while (42)
	{
		if (data->args->stop_p == 1)
			break ;
		j = 0;
		if (all_philo_are_thinking(data->philo))
		{
			while (j < data->args->nb_philos - 1)
			{
				data->philo[(i + j) % (data->args->nb_philos)].can_eat = 1;
				j += 2;
			}
			i += 1;
		}
		ft_usleep(5);
	}
	return (NULL);
}

void	*check_death(void *d)
{
	int		i;
	t_data	*data;

	data = (t_data *)d;
	while (42)
	{
		if (data->args->stop_p == 1)
			break ;
		i = 0;
		while (i < data->args->nb_philos)
		{
			philo_is_dead(&data->philo[i]);
			if (data->philo[i].status == DEAD)
			{
				break ;
			}
			i++;
		}
		ft_usleep(1);
	}
	return (NULL);
}

void	*philo_routine(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	while (philo->args->max_eat > 0 && philo->meal_count < philo->args->max_eat)
	{
		try_to_eat(philo);
	}
	philo->status = FINISHEAT;
	printf("\x1B[33m%lldms  Philo %d has eaten %d times on %d\n", ft_time() \
	- philo->init_time, philo->id, philo->meal_count, philo->args->max_eat);
	return (NULL);
}

void	process(t_data *data)
{
	int			i;
	pthread_t	monitor_thread;
	pthread_t	check_death_thread;

	i = -1;
	init_philosophers(data);
	if (pthread_create(&monitor_thread, NULL, monitor_philos, data) != 0)
		return ;
	while (++i < data->args->nb_philos)
		pthread_create(&(data->philo[i].thread), \
		NULL, philo_routine, (&data->philo[i]));
	if (pthread_create(&check_death_thread, NULL, check_death, data) != 0)
		return ;
	i = 0;
	while (i < data->args->nb_philos)
		pthread_join(data->philo[i++].thread, NULL);
	pthread_join(check_death_thread, NULL);
	pthread_join(monitor_thread, NULL);
	free(data->philo);
}
