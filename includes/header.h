/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgiordan <vgiordan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 14:30:06 by vgiordan          #+#    #+#             */
/*   Updated: 2023/05/03 17:13:35 by vgiordan         ###   ########.fr       */
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

typedef enum s_status
{
	DEAD,
	EATING,
	SLEEPTHINK,
	FINISHEAT,
}	t_status;

typedef struct s_args
{
	pthread_mutex_t	change_status;
	int				nb_philos;
	int				max_eat;
	int				stop_p;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
}	t_args;

typedef struct s_philo
{
	int				id;
	int				can_eat;
	int				meal_count;
	long long		last_meal_time;
	long long		init_time;
	pthread_t		thread;
	pthread_mutex_t	fork_mutex;
	struct s_philo	*next_philo;
	t_status		status;
	t_args			*args;
}	t_philo;

typedef struct s_datas
{
	t_philo	*philo;
	t_args	*args;
}	t_data;

/*<------------------ACTIONS------------------>*/

void		ph_sleep_and_think(t_philo *philo);
void		ph_eat(t_philo *philo);
int			take_forks(t_philo *philo);
void		lay_forks(t_philo *philo);
int			try_to_eat(t_philo *philo);
void		action(t_philo *philo);

/*<-------------------PHILO-------------------->*/

void		process(t_data *datada);

/*<----------------PHILO_ROUTINE---------------->*/

void		*philo_routine(void *data);

/*<--------------------UTILS-------------------->*/

int			philo_is_dead(t_philo *p);
void		display_status(t_philo *p, char *str);
long long	ft_time(void);
void		ft_usleep(long long time_in_ms, t_args *args);
int			all_philo_are_thinking(t_philo *p);
int			get_hungriest_philo(t_data *p);

/*<---------------------INIT--------------------->*/

void		init_philosophers(t_data *data);

long long	ft_atoi(const char *str);
void		ft_putstr_fd(char *s, int fd);

#endif