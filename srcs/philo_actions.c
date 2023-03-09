/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgiordan <vgiordan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 19:25:48 by vgiordan          #+#    #+#             */
/*   Updated: 2023/03/09 17:39:42 by vgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

void    ph_sleep(t_philo *philo)
{
	//pthread_mutex_lock(&(philo->write_mutex));
	ft_printf("Philo %d is sleeping\n", philo->id);
	//pthread_mutex_unlock(&(philo->write_mutex));
	//usleep(philo->args->time_to_sleep);
}

void    ph_eat(t_philo *philo)
{
	//printf("Mutex address %p\n", &(philo->write_mutex));
	//pthread_mutex_lock(&(philo->write_mutex));
	ft_printf("Philo %d is eating\n", philo->id);
	//pthread_mutex_unlock(&(philo->write_mutex));
	//usleep(philo->args->time_to_eat);
	lay_fork(philo);
}

void    ph_think(t_philo *philo)
{
	ft_printf("Philo %d is thinking\n", philo->id);
}

int	take_fork(t_philo *philo)
{
	/*if (pthread_mutex_lock(&(philo->fork_mutex)) != 0)
		return (0);
	if (pthread_mutex_lock(&(philo->next_philo->fork_mutex)) != 0)
	{
		ft_printf("Philo %d has not taken a fork\n", philo->id);
		if (pthread_mutex_unlock(&(philo->fork_mutex)) != 0)
			exit(1);
		return (0);
	}
	pthread_mutex_lock(&(philo->write_mutex));
	ft_printf("Philo %d has taken a fork\n", philo->id);
	pthread_mutex_unlock(&(philo->write_mutex));*/
	ph_eat(philo);
	return (1);
}

void	lay_fork(t_philo *philo)
{
	if (pthread_mutex_unlock(&(philo->fork_mutex)) != 0)
		exit(1);
	if (pthread_mutex_unlock(&(philo->next_philo->fork_mutex)) != 0)
		exit(1);
	ph_sleep(philo);
}

