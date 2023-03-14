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
	printf("Philo %d\nMeal Count %d\nlast_meal_time %lldms; pointeur %p next_ptr %p\n", p->id, p->meal_count, p->last_meal_time, p, p->next_philo);
	printf("------------\n");
}

long long ft_time()
{
	struct timeval  tv;
	long long time_in_mils;

	gettimeofday(&tv, NULL);
 	time_in_mils = (tv.tv_sec) * 1000 + (tv.tv_usec) / 1000;
	return (time_in_mils);
}

int	philo_is_dead(t_philo *philo)
{
	if(philo->status == EATING)
		return (0);
	//printf("\x1B[31m DELTA TIME EAT %lldms  Philo %d ::: MAX TIME %d\n", ft_time() - philo->init_time, philo->id, philo->args->time_to_die);
	philo->fork = 1;
	if (ft_time() - philo->last_meal_time - philo->init_time > philo->args->time_to_die)
	{
		philo->status = DEAD;
		printf("\x1B[31m%lldms  Philo %d died\n", ft_time() - philo->init_time, philo->id);
		return (1);
	}
	return (0);
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
