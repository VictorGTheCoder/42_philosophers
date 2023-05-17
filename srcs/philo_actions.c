/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgiordan <vgiordan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 19:25:48 by vgiordan          #+#    #+#             */
/*   Updated: 2023/05/17 18:28:07 by vgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

void	ph_sleep_and_think(t_philo *philo)
{
	philo->status = SLEEPTHINK;
	pthread_mutex_lock(&philo->args->stop_mutex);
	if (philo->args->stop_p == 1)
	{
		pthread_mutex_unlock(&philo->args->stop_mutex);
		return ;
	}
	pthread_mutex_unlock(&philo->args->stop_mutex);
	printf("\x1B[37m%lldms  Philo %d is sleeping\n", ft_time() \
			- philo->init_time, philo->id);
	ft_usleep(philo->args->time_to_sleep, philo);
	pthread_mutex_lock(&philo->args->stop_mutex);
	if (philo->args->stop_p == 1)
	{
		pthread_mutex_unlock(&philo->args->stop_mutex);
		return ;
	}
	pthread_mutex_unlock(&philo->args->stop_mutex);
	printf("\x1B[37m%lldms  Philo %d is thinking\n", ft_time() \
		- philo->init_time, philo->id);
}

void	ph_eat(t_philo *philo)
{
	long long	current_time;

	philo->status = EATING;
	current_time = ft_time() - philo->init_time;
	pthread_mutex_lock(&philo->args->stop_mutex);
	if (philo->args->stop_p == 1)
	{
		pthread_mutex_unlock(&philo->args->stop_mutex);
		return ;
	}
	pthread_mutex_unlock(&philo->args->stop_mutex);
	printf("\x1B[37m%lldms  Philo %d is eating\n", current_time, philo->id);
	philo->last_meal_time = ft_time();
	philo->meal_count += 1;
	ft_usleep(philo->args->time_to_eat, philo);
	lay_forks(philo);
}

void	lay_forks(t_philo *philo)
{
	pthread_mutex_unlock(&(philo->fork_mutex));
	pthread_mutex_unlock(&(philo->next_philo->fork_mutex));
	ph_sleep_and_think(philo);
}

int	take_forks(t_philo *philo)
{
	if (pthread_mutex_lock(&philo->fork_mutex) != 0)
		return (0);
	pthread_mutex_lock(&philo->args->stop_mutex);
	if (philo->args->stop_p == 1)
	{
		pthread_mutex_unlock(&philo->args->stop_mutex);
		return (0);
	}
	pthread_mutex_unlock(&philo->args->stop_mutex);
	printf("\x1B[37m%lldms  Philo %d has taken a fork\n", ft_time() \
		- philo->init_time, philo->id);
	if (pthread_mutex_lock(&philo->next_philo->fork_mutex) != 0)
		return (0);
	pthread_mutex_lock(&philo->args->stop_mutex);
	if (philo->args->stop_p == 1)
	{
		pthread_mutex_unlock(&philo->args->stop_mutex);
		return (0);
	}
	pthread_mutex_unlock(&philo->args->stop_mutex);
	printf("\x1B[37m%lldms  Philo %d has taken a fork\n", ft_time() \
		- philo->init_time, philo->id);
	ph_eat(philo);
	return (1);
}

int	try_to_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->args->stop_mutex);
	if (philo->status == DEAD || philo->args->stop_p == 1)
	{
		pthread_mutex_unlock(&philo->args->stop_mutex);
		return (0);
	}
	pthread_mutex_unlock(&philo->args->stop_mutex);
	take_forks(philo);
	return (1);
}
