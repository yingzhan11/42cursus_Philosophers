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

typedef pthread_mutex_t t_mtx;
typedef struct s_data t_data;


typedef struct s_philo
{
    int id;
    int meal_count;
    int last_eat_time;
    bool full;
    t_mtx *first_fork;
    t_mtx *second_fork;
    t_mtx philo_mtx;
    t_data *data;
} t_philo;

struct s_data
{
    //input
    int philo_nbr;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int meals_nbr;
    //philos & forks
    t_philo *philos;
    
    //mutex
    t_mtx *forks;
    

} ;


//tools
int show_error(char *error_info);


#endif