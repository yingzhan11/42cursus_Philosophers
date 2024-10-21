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

typedef enum e_opcode
{
    INIT,
} t_opcode;

typedef enum e_state
{
    READY,
    FULL,
    DIE,
    EATING,
    THINKING,
    SLEEPING,
} t_state;

typedef struct s_philo
{
    int id;
    int meal_count;
    long last_eat_time;
    bool full; 
    t_data *data;
    t_mtx *left_fork;
    t_mtx *right_fork;
    t_mtx philo_mtx;
    pthread_t thread_id;
    t_state state;
} t_philo;

struct s_data
{
    //input, time ms
    int philo_nbr;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int meals_nbr;
    long time_start;
    //philos & forks
    t_philo *philos;
    
    //mutex
    t_mtx *forks;
    t_mtx printer;
    

} ;

//init.c
int init_data(t_data *data);

//tools
int show_error(char *error_info);

//mutex_handler.c
int mutex_handler(t_mtx *mutex, t_opcode opcode);


#endif