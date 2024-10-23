/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhan <yzhan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 11:27:06 by yzhan             #+#    #+#             */
/*   Updated: 2024/10/23 11:31:38 by yzhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	put_down_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

int	pick_up_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	if (get_state(philo) == OVER)
	{
		pthread_mutex_unlock(philo->left_fork);
		return (-1);
	}
	print_info(philo, "has taken a fork");
	if (philo->data->philo_nbr == 1)
	{
		my_usleep(philo, philo->data->time_to_die * 2);
		pthread_mutex_unlock(philo->right_fork);
		return (-1);
	}
	pthread_mutex_lock(philo->right_fork);
	if (get_state(philo) == OVER)
	{
		put_down_forks(philo);
		return (-1);
	}
	print_info(philo, "has taken a fork");
	return (0);
}

long	calculate_time(t_time start)
{
	t_time	now;
	long	elapsed_time;

	if (gettimeofday(&now, NULL) == -1)
		return (-1);
	elapsed_time = (now.tv_sec - start.tv_sec) * 1000
		+ (now.tv_usec - start.tv_usec) / 1000;
	return (elapsed_time);
}

int	my_usleep(t_philo *philo, long time)
{
	t_time	this_start;
	long	elapsed_time;

	if (gettimeofday(&(this_start), NULL) == -1)
		return (-1);
	elapsed_time = 0;
	while (elapsed_time < time)
	{
		usleep(100);
		if (get_state(philo) == OVER)
		{
			if (philo->action == EATING)
				put_down_forks(philo);
			return (-1);
		}
		elapsed_time = calculate_time(this_start);
		if (elapsed_time == -1)
			return (-1);
	}
	return (0);
}

void	stop_all_threads(t_data *data, int thread_nbr)
{
	int	i;

	i = -1;
	while (++i < thread_nbr)
		set_state(&data->philos[i], OVER);
	i = -1;
	while (++i < thread_nbr)
	{
		if (pthread_join(data->philos[i].thread_id, NULL) != 0)
		{
			pthread_mutex_lock(&data->printer);
			printf("fail to join thread\n");
			pthread_mutex_unlock(&data->printer);
		}
	}
}
