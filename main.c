#include "philosopher.h"

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

int main(int ac, char **av)
{
    t_data data;

    if (ac != 5 && ac != 6)
        return(printf("fail"));
    if (!(is_num))
        return(printf("is not number"));
    
}

✅ 1. 파싱 및 데이터 구조 설계

인자 파싱 (ft_atoi 등)

t_data 또는 t_table 구조체 정의

철학자 배열 (t_philo) 구조체 정의

✅ 2. 구조체 초기화 함수 만들기

init_data(), init_philos(), init_mutex(), 등

✅ 3. 스레드 생성 (철학자 행동 정의)

철학자마다 pthread_create()로 스레드 실행

routine() 함수에서 행동 반복 구현 (think, eat, sleep)

✅ 4. 뮤텍스 설정

포크마다 pthread_mutex_t 생성

출력, 종료 플래그 등도 뮤텍스로 보호

✅ 5. 감시 스레드 구현 (모니터링)

철학자들이 일정 시간 밥을 안 먹으면 죽음 감지

옵션 인자 사용 시, 모든 철학자가 N번 먹으면 종료

✅ 6. 정확한 출력 처리

printf 또는 write 사용 시, 반드시 print_mutex로 동기화

✅ 7. 정리 및 리소스 해제

pthread_join(), pthread_mutex_destroy(), free() 등 리소스 정리