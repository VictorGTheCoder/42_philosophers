/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgiordan <vgiordan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 14:30:06 by vgiordan          #+#    #+#             */
/*   Updated: 2023/03/09 15:57:26 by vgiordan         ###   ########.fr       */
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

typedef struct	s_args
{
	int nb_philos;
	int time_to_die;
	int time_to_eat;
	int	time_to_sleep;
	int	max_eat;
	
}	t_args;

typedef struct s_philo
{
	int             id;
	int             state;
	int             last_meal_time;
	int             meal_count;
	int             left_fork;
	int             right_fork;
	int             init_time;
	int             init_utime;
	pthread_t       thread;
	pthread_mutex_t fork_mutex;
	struct s_philo	*next_philo;
	pthread_mutex_t write_mutex;
	t_args			*args;
} t_philo;

typedef struct s_philos
{
	t_philo *philos;
	t_args	*args;
}   t_philos;

/*<------------------ACTIONS------------------>*/

void    ph_sleep(t_philo *philo);
void    ph_eat(t_philo  *philo);
void    ph_think(t_philo  *philo);
int		take_fork(t_philo  *philo);
void	lay_fork(t_philo *philo);

/*<-------------------PHILO-------------------->*/

void    process(t_args *args);

/*<----------------PHILO_ROUTINE---------------->*/

void    *philo_routine(void *philo);

/*<--------------------UTILS-------------------->*/

int     philo_is_dead(t_philo *p);
void    display_status(t_philo *p, char *str);

/*<---------------------INIT--------------------->*/

void    init_philosophers(t_args *args, t_philo **p);

#endif