#include "philosopher.h"

int main(int ac, char **av)
{
    t_data data;

    if (ac != 5 && ac != 6)
        return(printf("fail"));
    if (is_num(ac, av) != 1)
        return(printf("is not number"));
    if(!(init_data(&data,ac,av)))
        return(prinft("init_error"));
    if (!create_threads(&data))
        return (printf("thread_error\n"));
 // 감시 + 종료 처리
    monitor_and_wait(&data);
    return 0;
}