/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeklee <jaeklee@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 14:25:04 by jaeklee           #+#    #+#             */
/*   Updated: 2025/09/10 16:42:37 by jaeklee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	free_resources(t_data *data)
{
	free(data->philo);
	free(data->forks);
}

void	print_status(t_philo *philo, char *msg)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&data->exit_mutex);
	if (!data->exit_flag)
	{
		pthread_mutex_lock(&data->print);
		printf("%ld %d %s\n", get_time_ms() - philo->data->start_time,
			philo->id, msg);
		pthread_mutex_unlock(&data->print);
	}
	pthread_mutex_unlock(&data->exit_mutex);
}

void	print_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->print);
	printf("%ld %d died\n", get_time_ms() - philo->data->start_time, philo->id);
	pthread_mutex_unlock(&philo->data->print);
}

int	p_error(char *s)
{
	printf("Error: %s\n", s);
	return (-1);
}
