/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgiordan <vgiordan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 19:26:18 by vgiordan          #+#    #+#             */
/*   Updated: 2023/03/14 10:23:46 by vgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

void    display_status(t_philo *p, char *str)
{

	(void) str;
	printf("------------\n");
	printf("Philo %d\nMeal Count %d\nlast_meal_time %ldms; pointeur %p next_ptr %p\n", p->id, p->meal_count, p->last_meal_time, p, p->next_philo);
	printf("------------\n");
}

long int ft_time()
{
	struct timeval  tv;
	long int time_in_mils;

	time_in_mils = 0;
	gettimeofday(&tv, NULL);
 	time_in_mils = tv.tv_sec * 1000 + (tv.tv_usec / 1000);
	return (time_in_mils);
}

int	philo_is_dead(t_philo *philo)
{

	if(philo->status == EATING)
		return (0);
	if(philo->status == DEAD)
		return (1);
	if (ft_time() - philo->last_meal_time - philo->init_time > philo->args->time_to_die)
	{
		philo->status = DEAD;
		printf("%ldms  Philo %d died\n", ft_time() - philo->init_time, philo->id);
		exit(1);
	}
	return (0);
}

t_philo *get_philo_need_to_eat(t_philo *philo)
{
	int	i;
	t_philo	*r;
	long long temp;

	i = 0;
	r = NULL;
	temp = philo->last_meal_time;
	while (i < philo->args->nb_philos)
	{
		if (philo->last_meal_time < temp)
			r = philo;
		philo = philo->next_philo;
		i++;
	}
	return (r);
}

void	ft_usleep(long int time_in_ms)
{
	long int	start_time;

	start_time = 0;
	start_time = ft_time();
	while ((ft_time() - start_time) < time_in_ms)
		usleep(time_in_ms / 10);
}

/*void    get_biggest_eat_time(t_philo *p)
{
	int i;
	int id;
	int temp;

	temp = 0;
	i = 0;
	id = 0;
	while (i < p->args->nb_philos)
	{
		if (p[i].last_meal_time > temp)
		{
			temp = p[i].last_meal_time;
			id = p[i].id;
		}
		i++;
	}
}*/
