#include "philo.h"

int show_error(char *error_info)
{
    printf("%s\n", error_info);
    return (-1);
}

void print_info(t_philo *philo, char *info)
{
    long elapsed_time;
    // char *str;

    if (get_state(philo) == OVER)
        return ;
    pthread_mutex_lock(&philo->data->printer);
    elapsed_time = calculate_time(philo->data->start_time);
    if (elapsed_time == -1)
        return ;
    if (info)
        printf("%ld   %d %s\n", elapsed_time, philo->id + 1, info);
    else if (philo->action == EATING)
	{
        printf("%ld   %d is eating", elapsed_time, philo->id + 1);
		printf(" %i meals\n", philo->meal_count + 1);
	}
    else if (philo->action == THINKING)
        printf("%ld   %d is thinking\n", elapsed_time, philo->id + 1);
    else if (philo->action == SLEEPING)
        printf("%ld   %d is sleeping\n", elapsed_time, philo->id + 1);
    // printf("%ld philo[%d] %s\n", elapsed_time, philo->id + 1, str);
    pthread_mutex_unlock(&philo->data->printer);
}

//clean function
