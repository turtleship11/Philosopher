#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <sys/time.h>
# include <pthread.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <stdio.h>


typedef struct s_data
{
    int philos;
    int time_to_eat;
    int time_to_die;
    int time_to_sleep;
    int num_of_eat;
    pthread_mutex_t *forks;
}   t_data;


#endif