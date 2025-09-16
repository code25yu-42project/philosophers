#include "philo_thread.h"

int	monitor(t_philo **philos, t_table *table)
{
	while (1)
	{
		if (monitor_timeseat(philos, table))
			return (TRUE);
		if (monitor_starve(philos, table))
			return (TRUE);
		if (is_philo_dead(table))
			return (TRUE);
		usleep_milli(10);
	}
	return (FALSE);
}

int	monitor_timeseat(t_philo **philos, t_table *table)
{
	int		i;
	long	times_eat;

	i = 0;
	if (table->times_eat < 0)
		return (FALSE);
	while (i < table->philo_num)
	{
		pthread_mutex_lock(&table->m_times);
		times_eat = (*philos)[i++].times_eat;
		pthread_mutex_unlock(&table->m_times);
		if (times_eat < table->times_eat)
			return (FALSE);
	}
	kill_philo(*philos, -1);
	return (TRUE);
}

int	monitor_starve(t_philo **philos, t_table *table)
{
	int		i;
	long	now;
	long	time_eat;

	i = 0;
	if (table->time_start <= 0)
		return (FALSE);
	while (i < table->philo_num)
	{
		pthread_mutex_lock(&table->m_times);
		gettimeofday_milli(&now);
		time_eat = (*philos)[i].time_eat;
		pthread_mutex_unlock(&table->m_times);
		if (now - time_eat > table->time_die)
		{
			kill_philo(*philos, i + 1);
			return (TRUE);
		}
		i++;
	}
	return (FALSE);
}

int	is_philo_dead(t_table *table)
{
	int	flag;

	pthread_mutex_lock(&table->m_die);
	flag = table->flag_die;
	pthread_mutex_unlock(&table->m_die);
	return (flag);
}

void	kill_philo(t_philo *philos, int kill_idx)
{
	long	now;

	pthread_mutex_lock(&philos->table->m_log);
	pthread_mutex_lock(&philos->table->m_die);
	philos->table->flag_die = kill_idx;
	pthread_mutex_unlock(&philos->table->m_die);
	gettimeofday_milli(&now);
	if (kill_idx > 0)
		printf("%ld %d %s\n", \
			now - philos->table->time_start, kill_idx, LOG_DIE);
	pthread_mutex_unlock(&philos->table->m_log);
}
