#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <sys/time.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

typedef struct s_philo t_philo;

typedef struct s_data
{
    int             philos;
    int             time_to_die;
    int             time_to_eat;
    int             time_to_sleep;
    int             num_of_eat;
    t_philo         *philo;    
    pthread_mutex_t *forks;
    pthread_mutex_t print;
    pthread_mutex_t exit_mutex;
    int             exit_flag;
	long start_time;
	long wait_time;
}   t_data;

typedef struct s_philo
{
    t_data      *data;
    int         id;      
    int         left_f;    
    int         right_f;   
    _Atomic int         meal;        
    _Atomic long        last_eat;   
    pthread_t   thread;   
} t_philo;

int	validate_data(t_data *data);
int init_mutex(t_data *data);
int	init_data(t_data *data, int ac, char **av);
void *monitor_routine(void *arg);
void print_status(t_philo *philo, char *msg);
void monitor_and_wait(t_data *data);
int check_exit(t_data *data);
void set_exit(t_data *data);
int is_num(int ac, char **av);;
int	ft_atoi(const char *str);
void unlock_forks_and_return(t_data *data, int first, int second);

long get_time_ms(void);
void think(t_philo *philo);
void eat(t_philo *philo);
void sleep_philo(t_philo *philo);
void *routine(void *arg);
int create_threads(t_data *data);
void print_death(t_philo *philo);
int	p_error(char *s);
long get_elapsed_time(t_data *data);

#endif
