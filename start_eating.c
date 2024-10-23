/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_eating.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhan <yzhan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 11:40:02 by yzhan             #+#    #+#             */
/*   Updated: 2024/10/23 11:42:48 by yzhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*philo's life cycle,
state OVER means this thread is already closed*/
static void	philo_loop(t_philo *philo)
{
	while (get_state(philo) != OVER)
	{
		if (ft_eating(philo) != 0)
			break ;
		if (ft_sleeping(philo) != 0)
			break ;
		ft_thinking(philo);
	}
}

/*function be execute inside each thread
odd ID philos, like 1, 3, 5 will start with thinking,
then go to the normal loop, this is to avoid a fork race*/
static void	*ft_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 != 0)
	{
		ft_thinking(philo);
		my_usleep(philo, philo->data->time_to_eat / 2);
	}
	philo_loop(philo);
	return (NULL);
}

/*create threads for each philo and monitor their state*/
int	start_eating(t_data *data)
{
	int			i;
	pthread_t	thread;

	i = -1;
	thread = 0;
	while (++i < data->philo_nbr)
	{
		if (pthread_create(&thread, NULL, &ft_philo, &data->philos[i]) != 0)
		{
			stop_all_threads(data, i);
			return (show_error("fail to create thread"));
		}
		data->philos[i].thread_id = thread;
	}
	monitor_philos(data);
	return (0);
}
