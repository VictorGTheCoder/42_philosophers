/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgiordan <vgiordan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 19:26:18 by vgiordan          #+#    #+#             */
/*   Updated: 2023/04/27 17:46:33 by vgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int	all_philo_are_thinking(t_philo *p)
{
	int	i;

	i = 0;
	while (i < p->args->nb_philos)
	{
		if (p->status != SLEEPTHINK && p->status != FINISHEAT)
			return (0);
		i++;
	}
	return (1);
}

long long	ft_time(void)
{
	struct timeval	tv;
	long long		time_in_mils;

	gettimeofday(&tv, NULL);
	time_in_mils = tv.tv_sec * 1000 + (tv.tv_usec / 1000);
	return (time_in_mils);
}

int	philo_is_dead(t_philo *philo)
{
	int	i;

	i = 0;
	if (ft_time() - philo->last_meal_time > philo->args->time_to_die
		&& philo->status != FINISHEAT)
	{
		philo->status = DEAD;
		philo->args->stop_p = 1;
		printf("%lldms  Philo %d died\n", ft_time()
			- philo->init_time, philo->id);
		return (1);
	}
	while (i < philo->args->nb_philos)
	{
		if (philo[i++].status != FINISHEAT)
			return (0);
	}
	philo->args->stop_p = 1;
	return (1);
}

void	ft_usleep(long long time_in_ms)
{
	long long	current_time;

	current_time = ft_time();
	while ((ft_time() - current_time) <= time_in_ms)
	{
		usleep(50);
		if ((ft_time() - current_time) >= time_in_ms)
			break ;
	}
}

int	get_hungriest_philo(t_data *data)
{
	int	i;
	int	id;
	int	temp;

	temp = ft_time();
	i = 0;
	id = 0;
	while (i < data->args->nb_philos)
	{
		if (data->philo[i].last_meal_time > temp)
		{
			temp = data->philo[i].last_meal_time;
			id = data->philo[i].id;
		}
		i++;
	}
	return (id);
}
