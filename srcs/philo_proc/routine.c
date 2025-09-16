#include "philo_proc.h"

void	child_routine(t_table *table)
{
	int		philo_num;

	philo_num = table->philo_num;
	if (pthread_create(&table->tid, NULL, &monitor, table))
		exit_philo(table, EXTERNAL_FAILURE);
	sem_wait(table->s_start_eat);
	sem_post(table->s_start_eat);
	gettimeofday_milli(&table->p_time_eat);
	if (table->idx % 2 == 0 \
	|| (philo_num % 2 && table->idx > 1 && table->idx == philo_num))
	{
		print_log(table, table->idx, LOG_SLEEP);
		usleep_milli(table->time_sleep);
		print_log(table, table->idx, LOG_THINK);
	}
	while (1)
	{
		take_fork(table);
		eat(table, table->time_eat);
		drop_fork(table, table->time_sleep);
	}
	if (pthread_detach(table->tid))
		exit_philo(table, EXTERNAL_FAILURE);
}	

void	take_fork(t_table *table)
{
	sem_wait(table->s_forks);
	print_log(table, table->idx, LOG_FORK);
	sem_wait(table->s_forks);
	print_log(table, table->idx, LOG_FORK);
}

void	eat(t_table *table, int time_eat)
{
	int	p_times_eat;

	sem_wait(table->s_times);
	gettimeofday_milli(&table->p_time_eat);
	sem_post(table->s_times);
	print_log(table, table->idx, LOG_EAT);
	usleep_milli(time_eat);
	sem_wait(table->s_times);
	table->p_times_eat++;
	p_times_eat = table->p_times_eat;
	sem_post(table->s_times);
	if (p_times_eat == table->times_eat)
		sem_post(table->s_end_eat);
}

void	drop_fork(t_table *table, int time_sleep)
{
	sem_post(table->s_forks);
	sem_post(table->s_forks);
	print_log(table, table->idx, LOG_SLEEP);
	usleep_milli(time_sleep);
	print_log(table, table->idx, LOG_THINK);
}
