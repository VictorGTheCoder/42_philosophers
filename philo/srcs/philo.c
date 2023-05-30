/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgiordan <vgiordan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 14:54:09 by vgiordan          #+#    #+#             */
/*   Updated: 2023/05/30 12:17:08 by vgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

static void	create_thread(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->args->nb_philos)
	{
		pthread_create(&(data->philo[i].thread), \
		NULL, philo_routine, (&data->philo[i]));
		i += 2;
	}
	usleep(5000);
	i = 1;
	while (i < data->args->nb_philos)
	{
		pthread_create(&(data->philo[i].thread), \
		NULL, philo_routine, (&data->philo[i]));
		i += 2;
	}
}

void	*philo_routine(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	while (philo->args->max_eat > 0 && philo->meal_count < philo->args->max_eat)
	{
		pthread_mutex_lock(&philo->args->stop_mutex);
		if (philo->args->stop_p == 1)
		{
			pthread_mutex_unlock(&philo->args->stop_mutex);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->args->stop_mutex);
		try_to_eat(philo);
	}
	philo->status = FINISHEAT;
	printf("\x1B[33m%lld %d has eaten %d times on %d\n", ft_time() \
	- philo->init_time, philo->id + 1, philo->meal_count, philo->args->max_eat);
	return (NULL);
}

void	solo_philo(t_data *data)
{
	pthread_mutex_lock(&data->philo->fork_mutex);
	printf("\x1B[37m%lld  1 has taken a fork\n", ft_time() \
		- data->philo->init_time);
	usleep(data->args->time_to_die * 1000);
	printf("\x1B[31m%lld  1 died\n", ft_time() \
		- data->philo->init_time);
	pthread_mutex_unlock(&data->philo->fork_mutex);
}

static void	loop_death_checker(t_data *data)
{
	int	i;

	i = 0;
	while (42)
	{
		if (i == data->args->nb_philos)
			i %= data->args->nb_philos;
		if (check_death(&(data->philo[i])) == 1)
		{
			break ;
		}
		i++;
	}
}

void	process(t_data *data)
{
	int			i;

	i = 0;
	pthread_mutex_init(&data->args->stop_mutex, NULL);
	init_philosophers(data);
	if (data->args->nb_philos == 1)
	{
		solo_philo(data);
	}
	else
	{
		create_thread(data);
		loop_death_checker(data);
		i = 0;
		while (i < data->args->nb_philos)
			pthread_join(data->philo[i++].thread, NULL);
	}
	free(data->philo);
}
