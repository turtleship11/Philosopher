/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeklee <jaeklee@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 16:51:37 by jaeklee           #+#    #+#             */
/*   Updated: 2025/09/10 16:57:49 by jaeklee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo	t_philo;

typedef struct s_data
{
	int					philos;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					num_of_eat;
	t_philo				*philo;
	pthread_mutex_t		*forks;
	pthread_mutex_t		print;
	pthread_mutex_t		exit_mutex;
	int					exit_flag;
	long				start_time;
}						t_data;

typedef struct s_philo
{
	t_data				*data;
	int					id;
	int					left_f;
	int					right_f;
	_Atomic int			meal;
	_Atomic long		last_eat;
	pthread_t			thread;
}	t_philo;

int						validate_data(t_data *data);
int						init_mutex(t_data *data);
int						init_data(t_data *data, int ac, char **av);
void					*monitor_routine(void *arg);
void					print_status(t_philo *philo, char *msg);
void					monitor_and_wait(t_data *data);
int						check_exit(t_data *data);
void					set_exit(t_data *data);
int						is_num(int ac, char **av);
int						init_philo(t_data *data, int i, long long current_time);
int						ft_atoi(const char *str);
void					unlock_forks_and_return(t_data *data, int first,
							int second);

long					get_time_ms(void);
void					think(t_philo *philo);
void					eat(t_philo *philo);
void					sleep_philo(t_philo *philo);
void					*routine(void *arg);
int						create_threads(t_data *data);
void					print_death(t_philo *philo);
int						p_error(char *s);
long					get_elapsed_time(t_data *data);

int						init_forks_and_philosophers(t_data *data,
							long long current_time);
void					free_resources(t_data *data);
int						check_death(t_data *data);
int						check_all_full(t_data *data);
int						take_forks(t_philo *philo);
#endif
