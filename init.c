
#include "philosopher.h"

int	validate_data(t_data *data)
{
	if (data->philos <= 0 || data->philos > 200)
		return (0);
	if (data->time_to_die < 0 || data->time_to_eat < 0 || data->time_to_sleep < 0)
		return (0);
	if (data->num_of_eat < 0)
		return (0);
	return (1);
}

int init_mutex(t_data data)
{
    
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
    if(!(init_mutex(data)))
        return (0);
}
