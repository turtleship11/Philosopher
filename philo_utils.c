#include "philosopher.h"

void unlock_forks_and_return(t_data *data, int first, int second)
{
    pthread_mutex_unlock(&data->forks[first]);
    pthread_mutex_unlock(&data->forks[second]);
    return;
}

int check_exit(t_data *data)
{
    int flag;
    pthread_mutex_lock(&data->exit_mutex);
    flag = data->exit_flag;
    pthread_mutex_unlock(&data->exit_mutex);
    return flag;
}

void set_exit(t_data *data)
{
    pthread_mutex_lock(&data->exit_mutex);
    data->exit_flag = 1;
    pthread_mutex_unlock(&data->exit_mutex);
}

int is_num(int ac, char **av)
{
    int i;
    int j;

    i = 1;
    while(i < ac)
    {
        j = 0;
        while (av[i][j])
        {
            if(!(av[i][j] >= '0' && av[i][j] <= '9'))
                return -1;
            j++;
        }
        i++;
    }
    return 1;
}

int	ft_atoi(const char *str)
{
	int	c;
	int	v;

	c = 1;
	v = 0;
	while (*str == ' ' || (*str >= 8 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			c = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		v = v * 10 + (*str - '0');
		str++;
	}
	return (v * c);
}
