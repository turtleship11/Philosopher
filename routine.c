#include "philosopher.h"

void *routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;
    t_data  *data  = philo->data;
    philo->last_eat = get_time_ms();

    while (!check_exit(data))
    {
        think(philo);
        if (check_exit(data)) break;

        eat(philo);
        if (check_exit(data)) break;

        if (data->num_of_eat > 0 && philo->meal >= data->num_of_eat)
            break;

        sleep_philo(philo);
        if (check_exit(data)) break;
    }
    return 0;
}



long get_time_ms(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void think(t_philo *philo)
{
    t_data *data = philo->data;
    long start;

    if (check_exit(data))
        return;

    print_status(philo, "is thinking");

    start = get_time_ms();
    while (!check_exit(data) && get_time_ms() - start < 100)
        usleep(1000);
}



void eat(t_philo *philo)
{
    t_data *data = philo->data;
    int first, second;

    if (check_exit(data))
        return;

    // 홀짝 데드락 방지: 먼저 집을 포크 결정
    if (philo->id % 2 == 0)
    {
        first = philo->left_f;
        second = philo->right_f;
    }
    else
    {
        first = philo->right_f;
        second = philo->left_f;
    }

    // 첫 번째 포크
    pthread_mutex_lock(&data->forks[first]);
    if (check_exit(data)) {
        pthread_mutex_unlock(&data->forks[first]);
        return;
    }
    print_status(philo, "has taken fork");

    // 두 번째 포크
    pthread_mutex_lock(&data->forks[second]);
    if (check_exit(data)) 
	{
        pthread_mutex_unlock(&data->forks[first]);
        pthread_mutex_unlock(&data->forks[second]);
        return;
    }
    print_status(philo, "has taken fork");

    // if (check_exit(data)) 
	// {
    //     pthread_mutex_unlock(&data->forks[first]);
    //     pthread_mutex_unlock(&data->forks[second]);
    //     return;
    // }

    print_status(philo, "is eating");
    philo->last_eat = get_time_ms();
    philo->meal++;

    long start = get_time_ms();
    while (!check_exit(data) && get_time_ms() - start < data->time_to_eat)
        usleep(100);

    // 포크 반납
    pthread_mutex_unlock(&data->forks[first]);
    pthread_mutex_unlock(&data->forks[second]);
}


void sleep_philo(t_philo *philo)
{
    t_data *data = philo->data;
    long start;

    print_status(philo, "is sleeping");
    start = get_time_ms();
    while (!check_exit(data) && get_time_ms() - start < data->time_to_sleep)
        usleep(1000);
}
