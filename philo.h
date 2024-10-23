/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhan <yzhan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 11:31:57 by yzhan             #+#    #+#             */
/*   Updated: 2024/10/23 11:39:45 by yzhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/*
unistd.h: write, uslepp
stdio.h: printf
stdlib.h: malloc, free
pthread.h: thread
sys/time.h: timeval
limits.h: INT_MAX
*/
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>

typedef struct timeval	t_time;
typedef pthread_mutex_t	t_mtx;
typedef struct s_data	t_data;

/*philo state
READY: all data of this philo has been initialized
FULL: philo meal_count > required meals_nbr
OVER: this philo thread is exited*/
typedef enum e_state
{
	READY,
	FULL,
	OVER,
}	t_state;

/*philo action*/
typedef enum e_action
{
	THINKING,
	EATING,
	SLEEPING,
}	t_action;

/*philo structure
id: 1~philo_nbr
meal_count: how many meals this philo eat
last_eat_time: the begin time of last meal
data: pointer to all simulation data
left_fork: own fork
right_fork: previous philo's fork
philo_mtx: mtx for this philo
thread_id: store thread handle id
state: philo's thread state, full or over
action: philo's current action, eat, sleep or think
*/
typedef struct s_philo
{
	int			id;
	int			meal_count;
	t_time		last_eat_time;
	t_data		*data;
	t_mtx		*left_fork;
	t_mtx		*right_fork;
	t_mtx		philo_mtx;
	pthread_t	thread_id;
	t_state		state;
	t_action	action;
}	t_philo;

/*data struction for the simulation
philo_nbr: > 0
time_to_die, time_to_eat, time_to_sleep: ms
meals_nbr: min meals for each philo(can be empty)
start_time: the start time of the simulation
forks: mutexes for all forks
printer: mutex for print info
philos: store all philos data
*/
struct s_data
{
	int		philo_nbr;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		meals_nbr;
	t_time	start_time;
	t_mtx	*forks;
	t_mtx	printer;
	t_philo	*philos;
} ;

/*start_eating.c
init threads and start the simulation*/
int		start_eating(t_data *data);

/*philo_action.c
philo's action functions*/
int		ft_eating(t_philo *philo);
int		ft_sleeping(t_philo *philo);
void	ft_thinking(t_philo *philo);

/*philo_tools.c
tools for threads, time calculation and eating*/
int		pick_up_forks(t_philo *philo);
void	put_down_forks(t_philo *philo);
long	calculate_time(t_time start);
int		my_usleep(t_philo *philo, long time);
void	stop_all_threads(t_data *data, int thread_nbr);

/*monitor.c*/
void	monitor_philos(t_data *data);

/*get_set.c
get or set value to struct with mutex management*/
int		get_state(t_philo *philo);
void	set_state(t_philo *philo, t_state state);
int		get_action(t_philo *philo);
int		set_action(t_philo *philo, t_action action);

/*tools.c*/
int		ft_atoi(char *str);
int		clean_all(t_data *data);
int		show_error(char *error_info);
void	print_info(t_philo *philo, char *info);

#endif
