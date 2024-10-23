/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhan <yzhan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 11:11:39 by yzhan             #+#    #+#             */
/*   Updated: 2024/10/23 11:13:15 by yzhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*get current state of the philo*/
int	get_state(t_philo *philo)
{
	int	state;

	pthread_mutex_lock(&philo->philo_mtx);
	state = philo->state;
	pthread_mutex_unlock(&philo->philo_mtx);
	return (state);
}

/*set a new state to philo*/
void	set_state(t_philo *philo, t_state state)
{
	pthread_mutex_lock(&philo->philo_mtx);
	philo->state = state;
	pthread_mutex_unlock(&philo->philo_mtx);
}

/*get current action of the philo*/
int	get_action(t_philo *philo)
{
	int	action;

	pthread_mutex_lock(&philo->philo_mtx);
	action = philo->action;
	pthread_mutex_unlock(&philo->philo_mtx);
	return (action);
}

/*set a new action to philo, and print info
if the action is eating, record the time to last_eat_time*/
int	set_action(t_philo *philo, t_action action)
{
	pthread_mutex_lock(&philo->philo_mtx);
	philo->action = action;
	if (philo->action == EATING)
	{
		if (gettimeofday(&(philo->last_eat_time), NULL) == -1)
			return (-1);
	}
	pthread_mutex_unlock(&philo->philo_mtx);
	print_info(philo, NULL);
	return (0);
}
