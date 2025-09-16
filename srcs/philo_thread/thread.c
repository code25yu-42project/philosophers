#include "philo_thread.h"

int	get_thread(t_philo **philos, t_table *table, int philo_num)
{
	int	i;

	i = 0;
	gettimeofday_milli(&table->time_start);
	pthread_mutex_lock(&table->m_pause);
	while (i < philo_num)
	{
		if (pthread_create(&(*philos)[i].tid, NULL, routine, &(*philos)[i]))
			return (EXTERNAL_FAILURE);
		i++;
	}
	i = 0;
	while (i < philo_num)
		gettimeofday_milli(&(*philos)[i++].time_eat);
	pthread_mutex_unlock(&table->m_pause);
	monitor(philos, table);
	return (RETURN_SUCCESS);
}

void	join_thread(t_philo **philos, int philo_num)
{
	int	i;

	i = 0;
	while (i < philo_num)
		pthread_join((*philos)[i++].tid, NULL);
}
