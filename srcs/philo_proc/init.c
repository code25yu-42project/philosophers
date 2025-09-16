#include "philo_proc.h"

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

int	init_pid(pid_t **pid, int philo_num)
{
	*pid = ft_calloc(philo_num, sizeof(pid_t));
	if (!*pid)
		return (MALLOC_FAILURE);
	return (RETURN_SUCCESS);
}

int	init_sem(t_table *table)
{
	sem_unlink("s_forks");
	sem_unlink("s_times");
	sem_unlink("s_die");
	sem_unlink("s_log");
	sem_unlink("s_start_eat");
	sem_unlink("s_end_eat");
	table->s_forks = sem_open("s_forks", O_CREAT, 0644, table->philo_num);
	table->s_times = sem_open("s_times", O_CREAT, 0644, 1);
	table->s_die = sem_open("s_die", O_CREAT, 0644, 1);
	table->s_log = sem_open("s_log", O_CREAT, 0644, 1);
	table->s_start_eat = sem_open("s_start_eat", O_CREAT, 0644, 1);
	table->s_end_eat = sem_open("s_end_eat", O_CREAT, 0644, 1);
	if (table->s_forks == SEM_FAILED || table->s_times == SEM_FAILED \
		|| table->s_die == SEM_FAILED || table->s_log == SEM_FAILED \
		|| table->s_start_eat == SEM_FAILED || table->s_end_eat == SEM_FAILED)
		return (EXTERNAL_FAILURE);
	return (RETURN_SUCCESS);
}
