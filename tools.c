#include "philo.h"

int show_error(char *error_info)
{
    printf("%s\n", error_info);
    return (-1);
}

long	calculate_time(t_time start)
{
	t_time	now;
	long	elapsed_time;

	if (gettimeofday(&now, NULL) == -1)
		return (-1);
	elapsed_time = (now.tv_sec - start.tv_sec) * 1000
		+ (now.tv_usec - start.tv_usec) / 1000;
	return (elapsed_time);
}
