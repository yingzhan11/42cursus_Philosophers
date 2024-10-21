#include "philo.h"

int mutex_handler(t_mtx *mutex, t_opcode opcode)
{
	if (opcode == INIT)
		return (pthread_mutex_init(mutex, NULL));
	return (show_error("wrong opcode for mutex handler"));
}
