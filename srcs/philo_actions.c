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
	pthread_mutex_lock(&(philo->args->write_mutex));
	printf("\x1B[37m%ldms  Philo %d is sleeping\n", ft_time() - philo->init_time, philo->id);
	pthread_mutex_unlock(&(philo->args->write_mutex));
	//pthread_mutex_unlock(&(philo->write_mutex));
	ft_usleep(philo->args->time_to_sleep);
	//philo_is_dead(philo);
	pthread_mutex_lock(&(philo->args->write_mutex));
	printf("\x1B[37m%ldms  Philo %d is thinking\n", ft_time() - philo->init_time, philo->id);
	pthread_mutex_unlock(&(philo->args->write_mutex));
}

void ph_eat(t_philo *philo)
{
	long int current_time;
    if (philo->status == DEAD)
        return;
    
    philo->status = EATING;
    current_time = ft_time() - philo->init_time;

	pthread_mutex_lock(&(philo->args->write_mutex));
    printf("\x1B[37m%ldms  Philo %d is eating\n", current_time, philo->id);
	pthread_mutex_unlock(&(philo->args->write_mutex));

    ft_usleep(philo->args->time_to_eat);
    philo->last_meal_time = current_time;
    philo->meal_count += 1;
    lay_forks(philo);
}
	
void	lay_forks(t_philo *philo)
{
	if (pthread_mutex_unlock(&(philo->fork_mutex)) != 0)
		exit(1);
	if (pthread_mutex_unlock(&(philo->next_philo->fork_mutex)) != 0)
		exit(1);
	philo->fork = 1;
	philo->next_philo->fork = 1;
	ph_sleep_and_think(philo);
}

int		take_forks(t_philo *philo)
{
	philo->fork = 0;
	philo->next_philo->fork = 0;
	if (pthread_mutex_lock(&(philo->fork_mutex)) != 0)
		return (0);
	pthread_mutex_lock(&(philo->args->write_mutex));
	printf("\x1B[37m%ldms  Philo %d has taken a fork\n", ft_time() - philo->init_time, philo->id);
	pthread_mutex_unlock(&(philo->args->write_mutex));
	if (pthread_mutex_lock(&(philo->next_philo->fork_mutex)) != 0)
		return (0);
	
	pthread_mutex_lock(&(philo->args->write_mutex));
	printf("\x1B[37m%ldms  Philo %d has taken a fork\n", ft_time() - philo->init_time, philo->id);
	pthread_mutex_unlock(&(philo->args->write_mutex));
	ph_eat(philo);
	return (1);
}

int	try_to_eat(t_philo *philo)
{
	if (philo == philo->next_philo)
		return (0);
	if (philo->status == DEAD)
		return (0);
	if (philo->fork == 1 && philo->next_philo->fork == 1)
	{
		take_forks(philo);
		return (1);
	}
	else
		return (0);
}