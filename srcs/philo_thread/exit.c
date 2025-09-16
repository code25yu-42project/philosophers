#include "philo_thread.h"

int	exit_philo(t_table *table, int errno)
{
	destroy_mutex(table);
	free_philo(table);
	if (errno)
		errmsg(errno);
	return (errno);
}

void	destroy_mutex(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_num)
		pthread_mutex_destroy(&table->forks[i++]);
	pthread_mutex_destroy(&table->m_die);
	pthread_mutex_destroy(&table->m_times);
	pthread_mutex_destroy(&table->m_log);
	pthread_mutex_destroy(&table->m_pause);
}

void	free_philo(t_table *table)
{
	if (table->philos)
		free(table->philos);
	if (table->forks)
		free(table->forks);
}

int	errmsg(int errno)
{
	ft_putstr_fd(PHILO, STDERR_FILENO);
	if (errno == INVALID_ARGV)
		ft_putstr_fd(MSG_INVALID_ARGV, STDERR_FILENO);
	else if (errno == MALLOC_FAILURE)
		ft_putstr_fd(MSG_MALLOC_FAILURE, STDERR_FILENO);
	else if (errno == EXTERNAL_FAILURE)
		ft_putstr_fd(MSG_EXTERNAL_FAILURE, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	return (errno);
}
