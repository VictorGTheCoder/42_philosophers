/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgiordan <vgiordan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 14:30:06 by vgiordan          #+#    #+#             */
/*   Updated: 2023/03/06 19:40:21 by vgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include "../libft/libft.h"

typedef struct s_philo
{
    int id;
    int state;
    int last_meal_time;
    int meal_count;
	pthread_t thread;
    int left_fork;
    int right_fork;
} t_philo;

typedef struct	args
{
	int nb_philos;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	t_philo	*philos;
}	t_args;


void    display_status(t_philo p, char *str);
void    init_philosophers(t_args *args);

#endif