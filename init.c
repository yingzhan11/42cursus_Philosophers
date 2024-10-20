#include "philo.h"

/*偶数philo先拿左边叉子，后拿右边叉子，奇数先右后左
拿到叉子的philo先吃，其他的会不动，都是从吃开始*/
void assign_forks(t_philo *philo, t_fork *forks, int position, int philo_nbr)
{
    if (i % 2 == 0)
    {
        philo->first_fork = forks[position];
        philo->second_fork = ;
    }
    else
    {
        
    }
    philo->first_fork = fork[position]
}

int philo_int(t_data *data)
{
    t_philo *philo;
    int i;

    i = -1;
    while (++i < data->philo_nbr)
    {
        philo = data->philos + i;
        philo->id = i + 1; //?????
        philo->meal_count = 0;
        philo->last_eat_time = 0;
        philo->full = false;
        philo->data = data;
        assign_forks(philo, data->forks, i, data->philo_nbr);
        mutex_handler(&philo->philo_mutex, INIT);
    }
}

int init_data(t_data *data)
{
    //malloc: philos
    data->philos = malloc(sizeof(t_philo) * data->philo_nbr);
    if (!data->philos)
        return (show_error("fail to malloc philos"));
    
    //mutex init: forks
    mutex_handler(&data->forks, INIT);

    //philo init
    philo_init(data);
}