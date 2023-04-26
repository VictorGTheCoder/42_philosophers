/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victo <victo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 14:30:06 by vgiordan          #+#    #+#             */
/*   Updated: 2023/04/26 19:13:34 by victo            ###   ########.fr       */
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
	int		max_eat;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	pthread_mutex_t write_mutex;
}	t_args;

typedef struct s_philo
{
	int             id;

	int             meal_count;
	int             fork;
	long long      	last_meal_time;
	long long     	init_time;
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
	
}   t_data;

/*<------------------ACTIONS------------------>*/

void    ph_sleep_and_think(t_philo *philo);
void    ph_eat(t_philo  *philo);
int		take_forks(t_philo  *philo);
void	lay_forks(t_philo *philo);
int		try_to_eat(t_philo *philo);

void	action(t_philo *philo);

/*<-------------------PHILO-------------------->*/

void    process(t_data *datada);

/*<----------------PHILO_ROUTINE---------------->*/

void    *philo_routine(void *data);

/*<--------------------UTILS-------------------->*/

int     philo_is_dead(t_philo *p);
void    display_status(t_philo *p, char *str);
long long	ft_time();
void	ft_usleep(long long time_in_ms);

/*<---------------------INIT--------------------->*/

void    init_philosophers(t_data *data);

#endif