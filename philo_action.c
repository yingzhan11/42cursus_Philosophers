#include "philo.h"

void put_down_forks(t_philo *philo)
{
    pthread_mutex_unlock(philo->left_fork);
    pthread_mutex_unlock(philo->right_fork);
}

int pick_up_forks(t_philo *philo)
{
    pthread_mutex_lock(philo->left_fork);
    if (check_state(philo) == OVER)
    {
        pthread_mutex_unlock(philo->left_fork);
        return (-1);
    }
    print_info(philo, "  picks up a fork");
    pthread_mutex_lock(philo->right_fork);
    if (check_state(philo) == OVER)
    {
        put_down_forks(philo);
        return (-1);
    }
    print_info(philo, "  picks up two forks");
    return (0);
}

int ft_eating(t_philo *philo)
{
    //pick up fork
    if (pick_up_forks(philo) != 0)
		return (-1);
    //change state and get eating time
    if (set_action(philo, EATING) != 0)
        return (-1);
    //spend eat time
    if (my_usleep(philo, philo->data->time_to_eat) != 0)
        return (-1);
    //put down forks
    put_down_forks(philo);
    //set eat count
    pthread_mutex_lock(&philo->philo_mtx);
    philo->meal_count++;
    if (philo->meal_count == philo->data->meals_nbr)
        philo->state = FULL;
    pthread_mutex_unlock(&philo->philo_mtx);
    return (0);
}

int ft_sleeping(t_philo *philo)
{
    set_action(philo, SLEEPING);
    if (my_usleep(philo, philo->data->time_to_sleep) != 0)
        return (-1);
    return (0);
}

void ft_thinking(t_philo *philo)
{
    set_action(philo, THINKING);
}

