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
