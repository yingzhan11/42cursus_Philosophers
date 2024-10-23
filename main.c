/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhan <yzhan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 11:13:35 by yzhan             #+#    #+#             */
/*   Updated: 2024/10/23 11:19:53 by yzhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	parse_input(t_data *data, char **argv)
{
	data->philo_nbr = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (data->philo_nbr <= 0)
		return (show_error("Too less philos"));
	if (data->time_to_die <= 0 || data->time_to_eat <= 0
		|| data->time_to_sleep <= 0)
		return (show_error("Wrong time arguments"));
	if (argv[5])
	{
		data->meals_nbr = ft_atoi(argv[5]);
		if (data->meals_nbr <= 0)
			return (show_error("Too less meals"));
	}
	else
		data->meals_nbr = -1;
	return (0);
}

/*偶数philo先拿左边叉子，后拿右边叉子，奇数先右后左
拿到叉子的philo先吃，其他的会不动，都是从吃开始*/
static void	assign_forks(t_philo *philo, t_mtx *forks, int i, int philo_nbr)
{
	philo->left_fork = &forks[i];
	if (i == 0)
		philo->right_fork = &forks[philo_nbr - 1];
	else
		philo->right_fork = &forks[i - 1];
}

static int	philo_init(t_data *data)
{
	t_philo	*philo;
	int		i;

	i = -1;
	while (++i < data->philo_nbr)
	{
		philo = data->philos + i;
		philo->id = i;
		philo->meal_count = 0;
		philo->last_eat_time.tv_sec = data->start_time.tv_sec;
		philo->last_eat_time.tv_usec = data->start_time.tv_usec;
		philo->data = data;
		assign_forks(philo, data->forks, i, data->philo_nbr);
		if (pthread_mutex_init(&philo->philo_mtx, NULL) != 0)
			return (show_error("fail to init philo mtx"));
		philo->state = READY;
		philo->action = THINKING;
	}
	return (0);
}

static int	init_data(t_data *data)
{
	int	i;

	if (gettimeofday(&(data->start_time), NULL) == -1)
		return (show_error("fail to gettimeofday"));
	data->forks = malloc(sizeof(t_mtx) * data->philo_nbr);
	if (!data->forks)
		return (show_error("fail to malloc forks"));
	i = -1;
	while (++i < data->philo_nbr)
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (show_error("fail to init fork mtx"));
	if (pthread_mutex_init(&data->printer, NULL) != 0)
		return (show_error("fail to init print mtx"));
	data->philos = malloc(sizeof(t_philo) * data->philo_nbr);
	if (!data->philos)
		return (show_error("fail to malloc philos"));
	if (philo_init(data) != 0)
		return (show_error("fail to init philos"));
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc == 5 || argc == 6)
	{
		if (parse_input(&data, argv) != 0)
			return (1);
		if (init_data(&data) != 0)
			return (clean_all(&data));
		if (start_eating(&data) != 0)
			return (clean_all(&data));
		clean_all(&data);
	}
	else
		return (show_error("Wrong number of arguments"));
	return (0);
}
