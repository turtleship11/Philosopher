/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeklee <jaeklee@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 12:53:55 by jaeklee           #+#    #+#             */
/*   Updated: 2025/09/10 14:24:35 by jaeklee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	validate_data(t_data *data)
{
	if (data->philos <= 0 || data->philos > 200)
		return (0);
	if (data->time_to_die < 0 || data->time_to_eat < 0
		|| data->time_to_sleep < 0)
		return (0);
	if (data->num_of_eat < 0)
		return (0);
	return (1);
}

int	init_mutex(t_data *data)
{
	long long	current_time;

	data->philo = malloc(sizeof(t_philo) * data->philos);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->philos);
	if (!data->philo || !data->forks)
	{
		free_resources(data);
		return (0);
	}
	current_time = get_time_ms();
	if (!init_forks_and_philosophers(data, current_time))
		return (0);
	if (pthread_mutex_init(&data->print, NULL) != 0)
	{
		free_resources(data);
		return (0);
	}
	data->exit_flag = 0;
	if (pthread_mutex_init(&data->exit_mutex, NULL) != 0)
	{
		free_resources(data);
		return (0);
	}
	return (1);
}

int	init_forks_and_philosophers(t_data *data, long long current_time)
{
	int	i;

	i = 0;
	while (i < data->philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0 || !init_philo(data,
				i, current_time))
		{
			free_resources(data);
			return (0);
		}
		i++;
	}
	return (1);
}

int	init_philo(t_data *data, int i, long long current_time)
{
	data->philo[i].id = i + 1;
	data->philo[i].data = data;
	data->philo[i].left_f = i;
	data->philo[i].right_f = (i + 1) % data->philos;
	data->philo[i].meal = 0;
	data->philo[i].last_eat = current_time;
	return (1);
}

int	init_data(t_data *data, int ac, char **av)
{
	if (!data)
		return (0);
	data->philos = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->num_of_eat = ft_atoi(av[5]);
	else
		data->num_of_eat = 0;
	if (!(validate_data(data)))
		return (0);
	if (!(init_mutex(data)))
	{
		return (0);
	}
	return (1);
}
