/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhan <yzhan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 11:25:19 by yzhan             #+#    #+#             */
/*   Updated: 2024/10/23 11:26:51 by yzhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_eating(t_philo *philo)
{
	if (pick_up_forks(philo) != 0)
		return (-1);
	if (set_action(philo, EATING) != 0)
		return (-1);
	if (my_usleep(philo, philo->data->time_to_eat) != 0)
		return (-1);
	put_down_forks(philo);
	pthread_mutex_lock(&philo->philo_mtx);
	philo->meal_count++;
	pthread_mutex_unlock(&philo->philo_mtx);
	if (philo->meal_count == philo->data->meals_nbr)
		set_state(philo, FULL);
	return (0);
}

int	ft_sleeping(t_philo *philo)
{
	set_action(philo, SLEEPING);
	if (my_usleep(philo, philo->data->time_to_sleep) != 0)
		return (-1);
	return (0);
}

void	ft_thinking(t_philo *philo)
{
	set_action(philo, THINKING);
}
