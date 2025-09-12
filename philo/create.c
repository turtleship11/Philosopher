/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeklee <jaeklee@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 12:53:51 by jaeklee           #+#    #+#             */
/*   Updated: 2025/09/12 21:07:54 by jaeklee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	create_threads(t_data *data)
{
	int	i;

	data->start_time = get_time_ms() + 10;
	i = 0;
	while (i < data->philos)
	{
		if (pthread_create(&data->philo[i].thread, NULL, routine,
				&data->philo[i]) != 0)
		{
			while (--i >= 0)
				pthread_join(data->philo[i].thread, NULL);
			return (0);
		}
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
