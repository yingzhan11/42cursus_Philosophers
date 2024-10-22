#include "philo.h"

void monitor_philos(t_data *data)
{
    while (1)
    {
        usleep(200);
        if (data->philo_nbr < 0)
            break ;
    }
}