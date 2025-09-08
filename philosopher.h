#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <sys/time.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>


typedef struct s_data
{
    int             philos;
    int             time_to_die;
    int             time_to_eat;
    int             time_to_sleep;
    int             num_of_eat;
    t_philo         *philo;        // 철학자 배열
    pthread_mutex_t *forks;        // 포크 배열 (뮤텍스)
    pthread_mutex_t print;         // 출력 뮤텍스
    pthread_mutex_t exit_mutex;
    int             exit_flag;
}   t_data;

typedef struct s_philo
{
    t_data      *data;       // 공용 데이터 접근용 포인터
    int         id;          // 철학자 번호 (1~N)
    int         left_f;      // 왼쪽 포크 인덱스
    int         right_f;     // 오른쪽 포크 인덱스
    int         meal;        // 몇 번 먹었는지
    long        last_eat;    // 마지막으로 먹은 시간
    pthread_t   thread;      // 쓰레드 ID
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

long get_time_ms(void);
void think(t_philo *philo);
void eat(t_philo *philo);
void sleep_philo(t_philo *philo);
void *routine(void *arg);
int create_threads(t_data *data);

#endif