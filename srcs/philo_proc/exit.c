#include "philo_proc.h"

int	exit_philo(t_table *table, int errno)
{
	close_sem(table);
	free_philo(table);
	if (errno)
		errmsg(errno);
	exit (errno);
}

void	close_sem(t_table *table)
{
	sem_close(table->s_forks);
	sem_close(table->s_times);
	sem_close(table->s_die);
	sem_close(table->s_log);
	sem_close(table->s_start_eat);
	sem_close(table->s_end_eat);
	sem_unlink("/s_forks");
	sem_unlink("/s_times");
	sem_unlink("/s_die");
	sem_unlink("/s_log");
	sem_unlink("/s_start");
	sem_unlink("/s_end");
}

void	free_philo(t_table *table)
{
	if (table->pid)
		free(table->pid);
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
