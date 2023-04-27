/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgiordan <vgiordan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 19:25:48 by vgiordan          #+#    #+#             */
/*   Updated: 2023/04/27 17:48:26 by vgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

void	ph_sleep_and_think(t_philo *philo)
{
	philo->status = SLEEPTHINK;
	printf("\x1B[37m%lldms  Philo %d is sleeping\n", ft_time() \
		- philo->init_time, philo->id);
	ft_usleep(philo->args->time_to_sleep);
	printf("\x1B[37m%lldms  Philo %d is thinking\n", ft_time() \
		- philo->init_time, philo->id);
}

void	ph_eat(t_philo *philo)
{
	long long	current_time;

	philo->status = EATING;
	current_time = ft_time() - philo->init_time;
	printf("\x1B[37m%lldms  Philo %d is eating\n", current_time, philo->id);
	philo->last_meal_time = ft_time();
	philo->meal_count += 1;
	ft_usleep(philo->args->time_to_eat);
	lay_forks(philo);
}

void	lay_forks(t_philo *philo)
{
	if (pthread_mutex_unlock(&(philo->fork_mutex)) != 0)
		exit(1);
	if (pthread_mutex_unlock(&(philo->next_philo->fork_mutex)) != 0)
		exit(1);
	ph_sleep_and_think(philo);
}

int	take_forks(t_philo *philo)
{
	if (pthread_mutex_lock(&philo->fork_mutex) != 0)
		return (0);
	printf("\x1B[37m%lldms  Philo %d has taken a fork\n", ft_time() \
		- philo->init_time, philo->id);
	if (pthread_mutex_lock(&philo->next_philo->fork_mutex) != 0)
		return (0);
	printf("\x1B[37m%lldms  Philo %d has taken a fork\n", ft_time() \
		- philo->init_time, philo->id);
	ph_eat(philo);
	return (1);
}

int	try_to_eat(t_philo *philo)
{
	if (philo == philo->next_philo)
		return (0);
	if (philo->status == DEAD)
		return (0);
	if (philo->can_eat == 1)
	{
		philo->can_eat = 0;
		take_forks(philo);
		return (1);
	}
	else
		return (0);
}
