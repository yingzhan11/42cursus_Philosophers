#include "philo.h"

void philo_loop(t_philo *philo)
{
	while (check_state(philo) != OVER)
	{
		// if (take_forks(philo) == 1) //TODO
		// 	break ;
		if (ft_eating(philo) != 0)
			break ;
		if (ft_sleeping(philo) != 0)
			break ;
		ft_thinking(philo);
	}
}

void *ft_philo(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
	{
		ft_thinking(philo);
		my_usleep(philo, philo->data->time_to_eat / 2);
	}
	philo_loop(philo);
	return (NULL);
}

int start_eating(t_data *data)
{
	int i;
	pthread_t thread;

	//thread init
	i = -1;
	//one_philo TODO
	while (++i < data->philo_nbr)
	{
		thread = data->philos[i].thread_id;
		if (pthread_create(&thread, NULL, &ft_philo, &data->philos[i]) != 0)
		{
			// stop_all_threads(data, i); //TODO
			return (show_error("fail to create thread"));
		}
	}
	//monitor
	monitor_philos(data); //TODO
	return (0);
}
