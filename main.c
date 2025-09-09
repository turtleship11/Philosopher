#include "philosopher.h"

int main(int ac, char **av)
{
    t_data data;

    if (ac != 5 && ac != 6)
        return(p_error("Error : invaild args"));
    if (is_num(ac, av) != 1)
        return(p_error("Error : is not number"));
    if(!(init_data(&data,ac,av)))
	{
        return(p_error("Error : init_error"));
	}
	data.start_time = get_time_ms();

    if (!create_threads(&data))
        return (p_error("Error : thread_error\n"));
    monitor_and_wait(&data);
    return 0;
}
