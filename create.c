/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeklee <jaeklee@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 12:53:51 by jaeklee           #+#    #+#             */
/*   Updated: 2025/09/10 12:59:38 by jaeklee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	create_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philos)
	{
		if (pthread_create(&data->philo[i].thread, NULL, routine,
				&data->philo[i]) != 0)
			return (0);
		i++;
	}
	return (1);
}

long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

long	get_elapsed_time(t_data *data)
{
	return (get_time_ms() - data->start_time);
}
