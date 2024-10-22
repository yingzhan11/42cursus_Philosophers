#ifndef PHILO_H
# define PHILO_H

/*
write, uslepp
printf
malloc, free
thread
timeval
INT_MAX
*/
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>
# include <stdbool.h>

typedef struct timeval t_time;
typedef pthread_mutex_t t_mtx;
typedef struct s_data t_data;


typedef enum e_state
{
    READY,
    FULL,
    DIE,
    OVER,
} t_state;

typedef enum e_action
{
    THINKING,
    EATING,
    SLEEPING,
} t_action;

typedef struct s_philo
{
    int id;
    int meal_count;
    t_time last_eat_time;
    t_data *data;
    t_mtx *left_fork;
    t_mtx *right_fork;
    t_mtx philo_mtx;
    pthread_t thread_id;
    t_state state;
    t_action action;
} t_philo;

struct s_data
{
    //input, time ms
    int philo_nbr;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int meals_nbr;
    t_time start_time;
        
    //mutex
    t_mtx *forks;
    t_mtx printer;
    
    //philos & forks
    t_philo *philos;

} ;

//init.c
int init_data(t_data *data);

//eating
int start_eating(t_data *data);

//action
int ft_eating(t_philo *philo);
int ft_sleeping(t_philo *philo);
void ft_thinking(t_philo *philo);
void put_down_forks(t_philo *philo);

//philo tools
int check_state(t_philo *philo);
int set_action(t_philo *philo, t_action action);
void print_info(t_philo *philo, char *info);
int my_usleep(t_philo *philo, long time);

void monitor_philos(t_data *data);

//tools
int show_error(char *error_info);
long	calculate_time(t_time start);

#endif