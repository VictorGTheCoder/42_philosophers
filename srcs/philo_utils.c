/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgiordan <vgiordan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 19:26:18 by vgiordan          #+#    #+#             */
/*   Updated: 2023/03/09 15:54:42 by vgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

void    display_status(t_philo *p, char *str)
{
	(void) str;
	printf("Philo %d\nMeal Count %d\nlast_meal_time %d pointeur %p next_ptr %p\n", p->id, p->meal_count, p->last_meal_time, p, p->next_philo);
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

int     philo_is_dead(t_philo *p)
{
	(void) p;
	return (0);
}