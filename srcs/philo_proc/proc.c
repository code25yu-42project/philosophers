#include "philo_proc.h"

void	get_proc(t_table *table)
{
	int	i;

	i = 0;
	get_thread_monitor(table);
	gettimeofday_milli(&table->time_start);
	sem_wait(table->s_start_eat);
	while (i < table->philo_num)
	{
		table->pid[i] = fork();
		if (table->pid[i] == -1)
			exit_philo(table, EXTERNAL_FAILURE);
		else if (table->pid[i] == 0)
		{
			table->idx = i + 1;
			child_routine(table);
		}
		i++;
	}
	sem_post(table->s_start_eat);
	parent_kill_proc(table, table->philo_num);
}

void	parent_kill_proc(t_table *table, int philo_num)
{
	int	status;
	int	i;

	i = 0;
	while (i++ < philo_num)
	{
		waitpid(-1, &status, 0);
		if (status)
		{
			i = 0;
			while (i < philo_num)
				kill(table->pid[i++], SIGKILL);
			sem_post(table->s_log);
			break ;
		}
	}
}

void	get_thread_monitor(t_table *table)
{
	pthread_t	tid;

	if (table->times_eat > 0)
	{
		if (pthread_create(&tid, NULL, &monitor_timeseat, table))
			exit_philo(table, EXTERNAL_FAILURE);
		if (pthread_detach(tid))
			exit_philo(table, EXTERNAL_FAILURE);
	}	
}

void	*monitor_timeseat(void *data)
{
	t_table	*table;
	int		i;

	i = 0;
	table = (t_table *)data;
	while (i++ < table->philo_num)
		sem_wait(table->s_end_eat);
	sem_post(table->s_end_eat);
	sem_wait(table->s_end_eat);
	i = 0;
	while (i < table->philo_num)
		kill(table->pid[i++], SIGKILL);
	sem_post(table->s_end_eat);
	exit(0);
}
