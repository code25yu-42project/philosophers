#include "philo_thread.h"

int	init_table(t_table *table, char *argv[])
{
	ft_memset(table, 0, sizeof(t_table));
	table->philo_num = ft_atoi(argv[1]);
	table->time_die = ft_atoi(argv[2]);
	table->time_eat = ft_atoi(argv[3]);
	table->time_sleep = ft_atoi(argv[4]);
	if (argv[5])
	{
		table->times_eat = ft_atoi(argv[5]);
		if (!(table->times_eat > 0))
			return (INVALID_ARGV);
	}
	else
		table->times_eat = -1;
	if (!(table->philo_num > 0 && table->time_die > 0 \
		&& table->time_eat > 0 && table->time_sleep > 0))
		return (INVALID_ARGV);
	return (RETURN_SUCCESS);
}

int	init_philos(t_philo **philos, t_table *table)
{
	int	i;

	*philos = ft_calloc(table->philo_num, sizeof(t_philo));
	if (!*philos)
		return (MALLOC_FAILURE);
	i = 0;
	while (i < table->philo_num)
	{
		(*philos)[i].idx = i + 1;
		(*philos)[i].lfork = i;
		(*philos)[i].rfork = (i + 1) % table->philo_num;
		(*philos)[i].table = table;
		i++;
	}
	return (RETURN_SUCCESS);
}

int	init_forks(pthread_mutex_t **forks, int fork_num)
{
	*forks = ft_calloc(fork_num, sizeof(pthread_mutex_t));
	if (!*forks)
		return (MALLOC_FAILURE);
	return (RETURN_SUCCESS);
}

int	init_mutex(t_table *table, int fork_num)
{
	int	i;

	i = 0;
	while (i < fork_num)
		if (pthread_mutex_init(&table->forks[i++], NULL))
			return (EXTERNAL_FAILURE);
	if (pthread_mutex_init(&table->m_die, NULL))
		return (EXTERNAL_FAILURE);
	if (pthread_mutex_init(&table->m_times, NULL))
		return (EXTERNAL_FAILURE);
	if (pthread_mutex_init(&table->m_log, NULL))
		return (EXTERNAL_FAILURE);
	if (pthread_mutex_init(&table->m_pause, NULL))
		return (EXTERNAL_FAILURE);
	return (RETURN_SUCCESS);
}
