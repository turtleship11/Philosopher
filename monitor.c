#include "philosopher.h"

void print_status(t_philo *philo, char *msg)
{
    pthread_mutex_lock(&philo->data->print);
    printf("%ld Philosopher %d %s\n", get_time_ms(), philo->id, msg);
    pthread_mutex_unlock(&philo->data->print);
}

void *monitor_routine(void *arg)
{
    t_data *data = (t_data *)arg;
    int i;

    while (1)
    {
        i = 0;
        while (i < data->philos)
        {
            // 1) 철학자가 죽었는지 확인
            long time_since_last_meal = get_time_ms() - data->philo[i].last_eat;
            if (time_since_last_meal > data->time_to_die)
            {
                print_status(&data->philo[i], "died");
                set_exit(data);  // 종료 플래그 설정
                return NULL;
            }

            // 2) 옵션 인자: 모든 철학자가 num_of_eat 이상 먹었는지 확인
            if (data->num_of_eat > 0)
            {
                int all_full = 1;
                for (int j = 0; j < data->philos; j++)
                {
                    if (data->philo[j].meal < data->num_of_eat)
                    {
                        all_full = 0;
                        break;
                    }
                }
                if (all_full)
                {
                    set_exit(data); // 종료 플래그 설정
                    return NULL;
                }
            }

            i++;
        }
        usleep(1000); // CPU 사용 줄이기
    }
    return NULL;
}


void monitor_and_wait(t_data *data)
{
    pthread_t monitor_thread;
    int i;

    // 감시 스레드 생성
    if (pthread_create(&monitor_thread, NULL, monitor_routine, data) != 0)
    {
        printf("monitor thread creation failed\n");
        return;
    }

    // 종료 플래그 체크
    while (!check_exit(data))
        usleep(1000);

    // 철학자 스레드 종료 대기
    i = 0;
    while (i < data->philos)
    {
        pthread_join(data->philo[i].thread, NULL);
        i++;
    }

    // 감시 스레드 종료
    pthread_join(monitor_thread, NULL);

    // 7-1) 뮤텍스 해제
    i = 0;
    while (i < data->philos)
    {
        pthread_mutex_destroy(&data->forks[i]);
        i++;
    }
    pthread_mutex_destroy(&data->print);
    pthread_mutex_destroy(&data->exit_mutex);

    // 7-2) 동적 메모리 해제
    free(data->philo);
    free(data->forks);
}
