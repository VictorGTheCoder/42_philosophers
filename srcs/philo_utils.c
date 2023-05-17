/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgiordan <vgiordan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 19:26:18 by vgiordan          #+#    #+#             */
/*   Updated: 2023/05/17 18:40:57 by vgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

long long	ft_time(void)
{
	struct timeval	tv;
	long long		time_in_mils;

	gettimeofday(&tv, NULL);
	time_in_mils = tv.tv_sec * 1000 + (tv.tv_usec / 1000);
	return (time_in_mils);
}

int	check_death(t_philo *philo)
{
	int	i;

	i = 0;
	if (ft_time() - philo->last_meal_time > philo->args->time_to_die
		&& philo->status != FINISHEAT)
	{
		philo->status = DEAD;
		pthread_mutex_lock(&philo->args->stop_mutex);
		philo->args->stop_p = 1;
		pthread_mutex_unlock(&philo->args->stop_mutex);
		printf("\x1B[31m%lldms  Philo %d died\n", ft_time()
			- philo->init_time, philo->id);
		return (1);
	}
	while (i < philo->args->nb_philos)
	{
		if (philo[i++].status != FINISHEAT)
			return (0);
	}
	return (1);
}

void	ft_usleep(long long time_in_ms, t_philo *philo)
{
	long long	current_time;

	current_time = ft_time();
	while ((ft_time() - current_time) <= time_in_ms)
	{
		pthread_mutex_lock(&philo->args->stop_mutex);
		if (philo->args->stop_p == 1)
		{
			pthread_mutex_unlock(&philo->args->stop_mutex);
			return ;
		}
		pthread_mutex_unlock(&philo->args->stop_mutex);
		if (check_death(philo) == 1)
			return ;
		usleep(500);
		if ((ft_time() - current_time) >= time_in_ms)
			break ;
	}
}
