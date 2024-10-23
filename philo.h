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

typedef struct timeval	t_time;
typedef pthread_mutex_t	t_mtx;
typedef struct s_data	t_data;

typedef enum e_state
{
	READY,
	FULL,
	OVER,
}	t_state;

typedef enum e_action
{
	THINKING,
	EATING,
	SLEEPING,
}	t_action;

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

//eating
int		start_eating(t_data *data);

//action
int		ft_eating(t_philo *philo);
int		ft_sleeping(t_philo *philo);
void	ft_thinking(t_philo *philo);

//philo tool
int		pick_up_forks(t_philo *philo);
void	put_down_forks(t_philo *philo);
long	calculate_time(t_time start);
int		my_usleep(t_philo *philo, long time);
void	stop_all_threads(t_data *data, int thread_nbr);

//monitor
void	monitor_philos(t_data *data);

//get & set
int		get_state(t_philo *philo);
void	set_state(t_philo *philo, t_state state);
int		get_action(t_philo *philo);
int		set_action(t_philo *philo, t_action action);

//tools
int		ft_atoi(char *str);
int		clean_all(t_data *data);
int		show_error(char *error_info);
void	print_info(t_philo *philo, char *info);

#endif
