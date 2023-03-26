/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgiordan <vgiordan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 19:25:48 by vgiordan          #+#    #+#             */
/*   Updated: 2023/03/14 10:51:45 by vgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"



void    ph_sleep_and_think(t_philo *philo)
{
	//pthread_mutex_lock(&(philo->write_mutex));
	//philo_is_dead(philo);
	philo->status = SLEEPTHINK;
	if (philo->status == DEAD)
		return ;
	printf("\x1B[37m%lldms  Philo %d is sleeping\n", ft_time() - philo->init_time, philo->id);
	//pthread_mutex_unlock(&(philo->write_mutex));
	usleep(philo->args->time_to_sleep * 1000);
	//philo_is_dead(philo);
	printf("\x1B[37m%lldms  Philo %d is thinking\n", ft_time() - philo->init_time, philo->id);
}

void ph_eat(t_philo *philo)
{
	long long current_time;
    if (philo->status == DEAD)
        return;
    
    philo->status = EATING;
    current_time = ft_time() - philo->init_time;
    printf("\x1B[37m%lldms  Philo %d is eating\n", current_time, philo->id);
    usleep(philo->args->time_to_eat * 1000);
    philo->last_meal_time = current_time;
    philo->meal_count += 1;
    lay_fork(philo);
}


int	take_fork(t_philo *philo)
{
	if (philo == philo->next_philo)
		return (0);
	if (philo->status == DEAD)
		return (0);
	if (philo->fork == 1)
	{
		philo->fork = 0;
		if (pthread_mutex_lock(&(philo->fork_mutex)) != 0)
			return (0);
		printf("\x1B[37m%lldms  Philo %d has taken a fork\n", ft_time() - philo->init_time, philo->id);
		if (philo->next_philo->fork == 1)
		{
			philo->next_philo->fork = 0;
			if (pthread_mutex_lock(&(philo->next_philo->fork_mutex)) != 0)
				return (0);
			printf("\x1B[37m%lldms  Philo %d has taken a fork\n", ft_time() - philo->init_time, philo->id);
			ph_eat(philo);
		}
		else
		{
			philo->fork = 1;
			pthread_mutex_unlock(&(philo->fork_mutex));
			usleep(philo->args->time_to_eat  * 1000 / 10);
		}
	}
	return (1);
}
	
void	lay_fork(t_philo *philo)
{
	if (pthread_mutex_unlock(&(philo->fork_mutex)) != 0)
		exit(1);
	if (pthread_mutex_unlock(&(philo->next_philo->fork_mutex)) != 0)
		exit(1);
	philo->fork = 1;
	philo->next_philo->fork = 1;
	ph_sleep_and_think(philo);
}

 