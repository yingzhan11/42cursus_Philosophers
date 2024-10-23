/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhan <yzhan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 11:25:19 by yzhan             #+#    #+#             */
/*   Updated: 2024/10/23 15:24:22 by yzhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*eating funtion
philo picks up forks firstly, then set the state and
do the real eat action.
when finish eating, put down forks, count meals times.
if the meal_count == meals_nbr, set the philo state to FULL*/
int	ft_eating(t_philo *philo)
{
	int	is_full;

	is_full = 0;
	if (pick_up_forks(philo) != 0)
		return (-1);
	if (set_action(philo, EATING) != 0)
		return (-1);
	if (my_usleep(philo, philo->data->time_to_eat) != 0)
		return (-1);
	put_down_forks(philo);
	pthread_mutex_lock(&philo->philo_mtx);
	philo->meal_count++;
	if (philo->meal_count == philo->data->meals_nbr)
		is_full = 1;
	pthread_mutex_unlock(&philo->philo_mtx);
	if (is_full == 1)
		set_state(philo, FULL);
	return (0);
}

/*sleep function
set sleep state and real sleep for time_to_sleep*/
int	ft_sleeping(t_philo *philo)
{
	set_action(philo, SLEEPING);
	if (my_usleep(philo, philo->data->time_to_sleep) != 0)
		return (-1);
	return (0);
}

/*think function
only need to set thinking action*/
void	ft_thinking(t_philo *philo)
{
	set_action(philo, THINKING);
}
