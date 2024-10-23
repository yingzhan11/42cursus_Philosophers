/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhan <yzhan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 11:21:54 by yzhan             #+#    #+#             */
/*   Updated: 2024/10/23 15:24:06 by yzhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*hungry_time is elapsed time from last meal
if hungry_time greater then time_to_die, the philo die*/
static int	check_die(t_philo *philo)
{
	long	hungry_time;
	t_time	last_eat_time;

	pthread_mutex_lock(&philo->philo_mtx);
	last_eat_time = philo->last_eat_time;
	pthread_mutex_unlock(&philo->philo_mtx);
	hungry_time = calculate_time(last_eat_time);
	if (hungry_time == -1)
		return (-1);
	if (hungry_time >= philo->data->time_to_die)
		return (1);
	return (0);
}

/*check is any philo die*/
static int	is_philo_die(t_data *data)
{
	int	i;
	int	res;

	i = -1;
	while (++i < data->philo_nbr)
	{
		res = check_die(&data->philos[i]);
		if (res != 0)
		{
			if (res == 1)
				print_info(&data->philos[i], "died");
			stop_all_threads(data, data->philo_nbr);
			return (1);
		}
	}
	return (0);
}

/*check if all philos full
if there is any philo is still hungry, return nbr
if all philos full, stop all theads and return 0*/
static int	is_philo_hungry(t_data *data)
{
	int	i;
	int	hungry;

	i = -1;
	hungry = data->philo_nbr;
	while (++i < data->philo_nbr)
	{
		if (get_state(&data->philos[i]) == FULL)
			hungry--;
	}
	if (hungry == 0)
		stop_all_threads(data, data->philo_nbr);
	return (hungry);
}

/*monitoring loop to check the state of philos
if one philo died, end simulation
if all philos full, end simulation*/
void	monitor_philos(t_data *data)
{
	while (1)
	{
		usleep(200);
		if (is_philo_die(data) != 0)
			break ;
		if (is_philo_hungry(data) == 0)
			break ;
	}
}
