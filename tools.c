#include "philo.h"

int show_error(char *error_info)
{
    printf("%s\n", error_info);
    return (-1);
}

// long calculate_time(long start_time)
// {
//     t_time current;
//     long ret_time;

//     if (gettimeofday(&current, NULL))
//         return (show_error("fail to gettimeofday"));
//     ret_time = (current.tv_sec * 1000) + (current.tv_usec / 1000);
//     if (start_time != 0)
//         ret_time = ret_time - start_time;
//     return (ret_time);
// }
