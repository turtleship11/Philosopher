#include "philosopher.h"

void print_status(t_philo *philo, char *msg)
{
    t_data *data = philo->data;

    pthread_mutex_lock(&data->exit_mutex);
    if (!data->exit_flag)
    {
        pthread_mutex_lock(&data->print);
        printf("%ld %d %s\n", get_time_ms() - philo->data->start_time, philo->id, msg);
        pthread_mutex_unlock(&data->print);
    }
    pthread_mutex_unlock(&data->exit_mutex);
}

void print_death(t_philo *philo)
{
    pthread_mutex_lock(&philo->data->print);
    printf("%ld %d died\n", get_time_ms() - philo->data->start_time, philo->id);
    pthread_mutex_unlock(&philo->data->print);
}

void *monitor_routine(void *arg)
{
    t_data *data;
    int i;

	data = (t_data *)arg;

	while (1)
	{
		i = 0;
		while (i < data->philos)
		{
			long time_since_last_meal = get_time_ms() - data->philo[i].last_eat;
			if (time_since_last_meal > data->time_to_die)
			{
				print_death(&data->philo[i]);
				set_exit(data);
				return NULL;
			}
			if (data->num_of_eat > 0)
			{
				int all_full = 1;
				int j = 0;

				while (j < data->philos)
				{
					if (data->philo[j].meal < data->num_of_eat)
					{
						all_full = 0;
						break;
					}
					j++;
				}
				if (all_full)
				{
					set_exit(data);
					return NULL;
				}
			}
			i++;
		}
		usleep(1000);
	}
    return NULL;
}


void monitor_and_wait(t_data *data)
{
    pthread_t monitor_thread;
    int i;

    if (pthread_create(&monitor_thread, NULL, monitor_routine, data) != 0)
    {
        printf("monitor thread creation failed\n");
        return;
    }
    while (!check_exit(data))
        usleep(1000);

    i = 0;
    while (i < data->philos)
    {
        pthread_join(data->philo[i].thread, NULL);
        i++;
    }

    pthread_join(monitor_thread, NULL);

    i = 0;
    while (i < data->philos)
    {
        pthread_mutex_destroy(&data->forks[i]);
        i++;
    }
    pthread_mutex_destroy(&data->print);
    pthread_mutex_destroy(&data->exit_mutex);

    free(data->philo);
    free(data->forks);
}
