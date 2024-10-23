#include "philo.h"

static int check_die(t_philo *philo)
{
    long hungry_time;
    t_time last_eat_time;

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

static int is_philo_die(t_data *data)
{
    int i;

    i = -1;
    while (++i < data->philo_nbr)
    {
        if (check_die(&data->philos[i]) != 0)
        {
            print_info(&data->philos[i], "died");
            stop_all_threads(data, data->philo_nbr);
            return (1);
        }
    }
    return (0);
}

static int is_philo_hungry(t_data *data)
{
    int i;
    int hungry;

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

void monitor_philos(t_data *data)
{
    while (1)
    {
        usleep(200); //why 200
        //one philo die
        if (is_philo_die(data) != 0)
            break ;
        //if all philos full
        if (is_philo_hungry(data) == 0)
            break ;
    }
}