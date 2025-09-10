/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeklee <jaeklee@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 12:53:25 by jaeklee           #+#    #+#             */
/*   Updated: 2025/09/10 16:47:34 by jaeklee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	*routine(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	while (get_time_ms() < data->start_time)
		usleep(100);
	philo->last_eat = data->start_time;
	if (data->philos == 1)
	{
		pthread_mutex_lock(&data->forks[philo->left_f]);
		think(philo);
		print_status(philo, "has taken a fork");
		usleep(data->time_to_die * 1000);
		set_exit(data);
		pthread_mutex_unlock(&data->forks[philo->left_f]);
		return (0);
	}
	while (!check_exit(data))
	{
		think(philo);
		eat(philo);
		sleep_philo(philo);
	}
	return (0);
}

void	think(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	if (!check_exit(data))
	{
		print_status(philo, "is thinking");
	}
}

void	sleep_philo(t_philo *philo)
{
	t_data	*data;
	long	start;

	data = philo->data;
	if (check_exit(data))
		return ;
	print_status(philo, "is sleeping");
	start = get_time_ms();
	while (!check_exit(data) && get_time_ms() - start < data->time_to_sleep)
		usleep(500);
}

int	take_forks(t_philo *philo)
{
	t_data	*data;
	int		first;
	int		second;

	data = philo->data;
	first = philo->left_f;
	second = philo->right_f;
	pthread_mutex_lock(&data->forks[first]);
	if (check_exit(data))
	{
		pthread_mutex_unlock(&data->forks[first]);
		return (0);
	}
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(&data->forks[second]);
	if (check_exit(data))
	{
		pthread_mutex_unlock(&data->forks[first]);
		pthread_mutex_unlock(&data->forks[second]);
		return (0);
	}
	print_status(philo, "has taken a fork");
	return (1);
}

void	eat(t_philo *philo)
{
	t_data	*data;
	long	start;

	data = philo->data;
	if (check_exit(data))
		return ;
	if (philo->id % 2 != 0)
		usleep(500);
	if (!take_forks(philo))
		return ;
	if (!check_exit(data))
	{
		print_status(philo, "is eating");
		philo->last_eat = get_time_ms();
		philo->meal++;
		start = get_time_ms();
		while (!check_exit(data) && get_time_ms() - start < data->time_to_eat)
			usleep(100);
	}
	pthread_mutex_unlock(&data->forks[philo->left_f]);
	pthread_mutex_unlock(&data->forks[philo->right_f]);
}

// void	eat(t_philo *philo)
// {
// 	t_data	*data;
// 	long	start;
// 	int		first;
// 	int		second;

// 	data = philo->data;
// 	if (check_exit(data))
// 	{
// 		return ;
// 	}
// 	if (philo->id % 2 != 0)
// 		usleep(500);
// 	first = philo->left_f;
// 	second = philo->right_f;
// 	pthread_mutex_lock(&data->forks[first]);
// 	if (check_exit(data))
// 	{
// 		pthread_mutex_unlock(&data->forks[first]);
// 		return ;
// 	}
// 	print_status(philo, "has taken a fork");
// 	pthread_mutex_lock(&data->forks[second]);
// 	if (check_exit(data))
// 	{
// 		pthread_mutex_unlock(&data->forks[first]);
// 		pthread_mutex_unlock(&data->forks[second]);
// 		return ;
// 	}
// 	print_status(philo, "has taken a fork");
// 	if (!check_exit(data))
// 	{
// 		print_status(philo, "is eating");
// 		philo->last_eat = get_time_ms();
// 		philo->meal++;
// 		start = get_time_ms();
// 		while (!check_exit(data) && get_time_ms() - start < data->time_to_eat)
// 		{
// 			usleep(100);
// 		}
// 	}
// 	pthread_mutex_unlock(&data->forks[first]);
// 	pthread_mutex_unlock(&data->forks[second]);
// }
