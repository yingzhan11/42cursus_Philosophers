#include "philo.h"

static int	ft_atoi(char *str)
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

static int parse_input(t_data *data, char **argv)
{
    data->philo_nbr = ft_atoi(argv[1]);
    data->time_to_die = ft_atoi(argv[2]);
    data->time_to_eat = ft_atoi(argv[3]);
    data->time_to_sleep = ft_atoi(argv[4]);
    if (data->philo_nbr <= 0)
        return (show_error("Too less philos"));
    if (data->time_to_die <= 0 || data->time_to_eat <= 0
        || data->time_to_sleep <= 0)
        return (show_error("Wrong time arguments"));
    if (argv[5])
    {
        data->meals_nbr = ft_atoi(argv[5]);
        if (data->meals_nbr <= 0)
            return (show_error("Too less meals"));
    }
    else
        data->meals_nbr = -1;
    return (0);
}

int main(int argc, char **argv)
{
    t_data data;
 
    if (argc == 5 || argc == 6)
    {
        if (parse_input(&data, argv) != 0)
            return (1);
        if (init_data(&data) != 0)
            return (clean_all(&data));
        if (start_eating(&data) != 0)
            return (clean_all(&data));
        clean_all(&data);
    }
    else
        return (show_error("Wrong number of arguments"));
    return (0);
}