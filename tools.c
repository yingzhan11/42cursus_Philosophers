/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhan <yzhan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 11:43:27 by yzhan             #+#    #+#             */
/*   Updated: 2024/10/23 11:46:42 by yzhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*valid input input: [spaces][+][0~9] < INT_MAX
eg. "    +200", "   100", "200"*/
int	ft_atoi(char *str)
{
	int		i;
	long	num;

	i = 0;
	num = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			return (-1);
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = (str[i++] - '0') + (num * 10);
		if (num > INT_MAX)
			return (-1);
	}
	if (str[i] != '\0')
		return (-1);
	return ((int)num);
}

/*destroy all mutexes and free memory*/
int	clean_all(t_data *data)
{
	int	i;

	i = -1;
	if (data->forks)
	{
		while (++i < data->philo_nbr)
			pthread_mutex_destroy(&data->forks[i]);
		free(data->forks);
	}
	pthread_mutex_destroy(&data->printer);
	i = -1;
	if (data->philos)
	{
		while (++i < data->philo_nbr)
			pthread_mutex_destroy(&data->philos[i].philo_mtx);
		free(data->philos);
	}
	return (1);
}

int	show_error(char *error_info)
{
	printf("%s\n", error_info);
	return (-1);
}

/*print philos action info with mutex*/
void	print_info(t_philo *philo, char *info)
{
	long	elapsed_time;

	if (get_state(philo) == OVER)
		return ;
	pthread_mutex_lock(&philo->data->printer);
	elapsed_time = calculate_time(philo->data->start_time);
	if (elapsed_time == -1)
		return ;
	if (info)
		printf("%ld %d %s\n", elapsed_time, philo->id, info);
	else if (philo->action == EATING)
		printf("%ld %d is eating\n", elapsed_time, philo->id);
	else if (philo->action == THINKING)
		printf("%ld %d is thinking\n", elapsed_time, philo->id);
	else if (philo->action == SLEEPING)
		printf("%ld %d is sleeping\n", elapsed_time, philo->id);
	pthread_mutex_unlock(&philo->data->printer);
}
