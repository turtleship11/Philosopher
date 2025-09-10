/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeklee <jaeklee@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 12:53:48 by jaeklee           #+#    #+#             */
/*   Updated: 2025/09/10 16:39:14 by jaeklee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	check_death(t_data *data)
{
	int		i;
	long	time_since_last_meal;

	i = 0;
	while (i < data->philos)
	{
		time_since_last_meal = get_time_ms() - data->philo[i].last_eat;
		if (time_since_last_meal >= data->time_to_die)
		{
			print_death(&data->philo[i]);
			set_exit(data);
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_all_full(t_data *data)
{
	int	all_full;
	int	j;

	if (data->num_of_eat > 0)
	{
		all_full = 1;
		j = 0;
		while (j < data->philos)
		{
			if (data->philo[j].meal < data->num_of_eat)
			{
				all_full = 0;
				break ;
			}
			j++;
		}
		if (all_full)
		{
			set_exit(data);
			return (1);
		}
	}
	return (0);
}

void	*monitor_routine(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (1)
	{
		if (check_death(data))
			return (NULL);
		if (check_all_full(data))
			return (NULL);
	}
	return (NULL);
}

void	monitor_and_wait(t_data *data)
{
	pthread_t	monitor_thread;
	int			i;

	if (pthread_create(&monitor_thread, NULL, monitor_routine, data) != 0)
	{
		printf("monitor thread creation failed\n");
		return ;
	}
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
