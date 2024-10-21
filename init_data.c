#include "philo.h"

/*偶数philo先拿左边叉子，后拿右边叉子，奇数先右后左
拿到叉子的philo先吃，其他的会不动，都是从吃开始*/
void assign_forks(t_philo *philo, t_mtx *forks, int position, int philo_nbr)
{
    philo->left_fork = &forks[position];
    if (position == 0)
        philo->right_fork = &forks[philo_nbr - 1];
    else
        philo->right_fork = &forks[position - 1];
}

int philo_init(t_data *data)
{
    t_philo *philo;
    int i;

    i = -1;
    while (++i < data->philo_nbr)
    {
        philo = data->philos + i;
        philo->id = i; // + 1?????
        philo->meal_count = 0;
        philo->last_eat_time = 0;
        philo->full = false;
        philo->data = data;
        assign_forks(philo, data->forks, i, data->philo_nbr);
        if (mutex_handler(&philo->philo_mtx, INIT) != 0)
            return (show_error("fail to init philo mtx"));
        philo->state = READY;
    }
    return (0);
}

int init_data(t_data *data)
{
    int i;

    //malloc: philos
    data->philos = malloc(sizeof(t_philo) * data->philo_nbr);
    if (!data->philos)
        return (show_error("fail to malloc philos"));
    
    //mutex init: forks
    data->forks = malloc(sizeof(t_mtx) * data->philo_nbr);
    if (!data->forks)
        return (show_error("fail to malloc forks"));
    i = -1;
    while (++i < data->philo_nbr)
        if (mutex_handler(&data->forks[i], INIT) != 0)
            return (show_error("fail to init fork mtx"));

    //philo init
    if (philo_init(data) != 0)
        return (show_error("fail to init philos"));
    return (0);
}
