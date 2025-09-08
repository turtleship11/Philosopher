#include "philosopher.h"

int create_threads(t_data *data)
{
    int i;

    i = 0;
    while (i < data->philos)
    {
        if (pthread_create(&data->philo[i].thread, NULL, routine, &data->philo[i]) != 0)
            return 0; // 스레드 생성 실패
        i++;
    }
    return 1;
}

void *routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;
    t_data  *data  = philo->data;

    while (!check_exit(data))
    {
        think(philo);
        eat(philo);
        // num_of_eat 옵션: 지정 횟수 이상 먹으면 루프 탈출
        if (data->num_of_eat > 0 && philo->meal >= data->num_of_eat)
            break;
        sleep_philo(philo);
    }
    return 0;  // 루프 종료 시 스레드 종료
}


long get_time_ms(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void think(t_philo *philo)
{
    print_status(philo, "is thinking");
    usleep(100); // 잠깐 생각
}

void eat(t_philo *philo)
{
    t_data *data = philo->data;

    // 홀짝 데드락 방지
    if (philo->id % 2 == 0)
    {
        pthread_mutex_lock(&data->forks[philo->left_f]);
        print_status(philo, "has taken left fork");
        pthread_mutex_lock(&data->forks[philo->right_f]);
        print_status(philo, "has taken right fork");
    }
    else
    {
        pthread_mutex_lock(&data->forks[philo->right_f]);
        print_status(philo, "has taken right fork");
        pthread_mutex_lock(&data->forks[philo->left_f]);
        print_status(philo, "has taken left fork");
    }
    // 식사
    print_status(philo, "is eating");
    philo->last_eat = get_time_ms();
    philo->meal++;
    usleep(data->time_to_eat * 1000);

    // 포크 내려놓기
    pthread_mutex_unlock(&data->forks[philo->left_f]);
    pthread_mutex_unlock(&data->forks[philo->right_f]);
}

void sleep_philo(t_philo *philo)
{
    print_status(philo, "is sleeping");
    usleep(philo->data->time_to_sleep * 1000);
}
