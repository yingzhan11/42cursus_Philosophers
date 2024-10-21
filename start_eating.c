#include "philo.h"

int check_state(t_philo *philo)
{
	int ret;

	pthread_mutex_lock(&philo->philo_mtx);
	ret = philo->state;
	pthread_mutex_unlock(&philo->philo_mtx);
	return (ret);
}

void philo_loop(t_philo *philo)
{
	int philo_state;

	philo_state = check_state(philo);
	while (philo_state != FULL || philo_state != DIE)
	{
		if (take_forks(philo) == -1) //TODO
			break ;
		if (ft_eating(philo) == -1) //TODO
			break ;
		if (ft_sleeping(philo) == -1) //TODO
			break ;
		ft_thinking(philo); //TODO
	}
}

void *ft_philo(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
	{
		ft_thinking(philo); //TODO
		my_usleep(philo, philo->data->time_to_eat / 2);
	}
	philo_loop(philo);
	return (NULL);
}

int start_eating(t_data *data)
{
	int i;
	pthread_t thread_id;

	//get start_time (millisecond ms)

	//thread init
	i = -1;
	while (++i < data->philo_nbr)
	{
		thread_id = data->philos[i].thread_id;
		if (pthread_create(&thread_id, NULL, &ft_philo, &data->philos[i]) != 0)
		{
			stop_all_threads(data, i); //TODO
			return (("fail to create thread"));
		}
	}
	//monitor
	monitor_philos(data); //TODO
	return (0);
}
