#include "philo.h"

int check_state(t_philo *philo)
{
	int ret;

	pthread_mutex_lock(&philo->philo_mtx);
	ret = philo->state;
	pthread_mutex_unlock(&philo->philo_mtx);
	return (ret);
}

int set_action(t_philo *philo, t_action action)
{
    pthread_mutex_lock(&philo->philo_mtx);
    philo->action = action;
    if (philo->action == EATING)
    {
        // philo->last_eat_time = calculate_time (0);
        if (gettimeofday(&(philo->last_eat_time), NULL) == -1)
		    return (-1);  
        // if (philo->last_eat_time == -1)
        //     return (-1);
    }
    pthread_mutex_unlock(&philo->philo_mtx);
    print_info(philo, NULL);
    return (0);
}

void print_info(t_philo *philo, char *info)
{
    long elapsed_time;
    char *str;

    if (check_state(philo) == OVER)
        return ;
    pthread_mutex_lock(&philo->data->printer);
    elapsed_time = passed_time(philo->data->start_time);
    if (elapsed_time == -1)
        return ;
    if (info)
        str = info;
    else if (philo->action == EATING)
        str = "is eating";
    else if (philo->action == THINKING)
        str = "is thinking";
    else if (philo->action == SLEEPING)
        str = "is sleeping";
    printf("%ld philo[%d] %s\n", elapsed_time, philo->id + 1, str);
    pthread_mutex_unlock(&philo->data->printer);
}

long	passed_time(t_time start)
{
	t_time	curr;
	long	ms;

	if (gettimeofday(&curr, NULL) == -1)
		return (-1);
	ms = (curr.tv_sec - start.tv_sec) * 1000
		+ (curr.tv_usec - start.tv_usec) / 1000;
	return (ms);
}

int my_usleep(t_philo *philo, long time)
{
	t_time this_start;
    // t_time elapsed_time;

    if (gettimeofday(&(this_start), NULL) == -1)
		return (-1);
    // elapsed_time.tv_sec = this_start.tv_sec;
    // elapsed_time.tv_usec = this_start.tv_usec;

    while (passed_time(this_start) < time)
    {
        usleep(100);
        if (check_state(philo) == OVER)
        {
            if (philo->action == EATING)
                put_down_forks(philo);
            return (-1);
        }
        // elapsed_time = calculate_time(this_start);
        // if (elapsed_time == -1)
        //     return (-1);
    }
    return (0);
    
}