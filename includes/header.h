/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgiordan <vgiordan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 14:30:06 by vgiordan          #+#    #+#             */
/*   Updated: 2023/03/14 10:54:52 by vgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H
# define INT_MAX 2147483647
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include "../libft/libft.h"

typedef enum s_status
{
	DEAD,
	EATING,
	SLEEPTHINK
	
} t_status;

typedef struct	s_args
{
	int		nb_philos;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		max_eat;
}	t_args;

typedef struct s_philo
{
	int             id;

	int             meal_count;
	int             fork;
	long long       last_meal_time;
	long long      	init_time;
	pthread_t       thread;
	pthread_mutex_t fork_mutex;
	struct s_philo	*next_philo;
	t_status         status;
	pthread_mutex_t *write_mutexcpy;
	t_args			*args;
} t_philo;

typedef struct s_datas
{
	t_philo *philo;
	t_args	*args;
	pthread_mutex_t write_mutex;
}   t_data;

/*<------------------ACTIONS------------------>*/

void    ph_sleep_and_think(t_philo *philo);
void    ph_eat(t_philo  *philo);
int		take_fork(t_philo  *philo);
void	lay_fork(t_philo *philo);
void	action(t_philo *philo);

/*<-------------------PHILO-------------------->*/

void    process(t_data *datada);

/*<----------------PHILO_ROUTINE---------------->*/

void    *philo_routine(void *data);

/*<--------------------UTILS-------------------->*/

int     philo_is_dead(t_philo *p);
void    display_status(t_philo *p, char *str);
long long	ft_time();

/*<---------------------INIT--------------------->*/

void    init_philosophers(t_data *data);

#endif