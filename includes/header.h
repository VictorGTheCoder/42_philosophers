#ifndef HEADER_H
# define HEADER_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include "../libft/libft.h"

typedef struct philo
{
    pthread_t   thread_nb;
    int         status;
}   t_p;

#endif