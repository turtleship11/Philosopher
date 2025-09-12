/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeklee <jaeklee@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 12:53:33 by jaeklee           #+#    #+#             */
/*   Updated: 2025/09/11 17:15:56 by jaeklee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 5 && ac != 6)
		return (p_error("invaild args"));
	if (is_num(ac, av) != 1)
		return (p_error("Invaild input"));
	if (!(init_data(&data, ac, av)))
	{
		return (p_error("init_error or value is too big"));
	}
	data.start_time = get_time_ms();
	if (!create_threads(&data))
		return (p_error("thread_error\n"));
	monitor_and_wait(&data);
	return (0);
}
