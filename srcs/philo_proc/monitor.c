#include "philo_proc.h"

void	*monitor(void *data)
{
	t_table	*table;

	table = (t_table *)data;
	while (1)
	{
		monitor_starve(table);
		usleep_milli(10);
	}
}

void	monitor_starve(t_table *table)
{
	long	now;
	long	p_time_eat;

	if (table->p_time_eat <= 0)
		return ;
	sem_wait(table->s_times);
	gettimeofday_milli(&now);
	p_time_eat = table->p_time_eat;
	sem_post(table->s_times);
	if (now - p_time_eat > table->time_die)
		kill_philo_bonus(table, table->idx);
}

int	is_philo_dead(t_table *table)
{
	int	flag;

	sem_wait(table->s_die);
	flag = table->flag_die;
	sem_post(table->s_die);
	return (flag);
}

void	kill_philo_bonus(t_table *table, int kill_idx)
{
	long	now;
	int		i;

	sem_wait(table->s_log);
	sem_wait(table->s_die);
	table->flag_die = kill_idx;
	sem_post(table->s_die);
	gettimeofday_milli(&now);
	if (kill_idx > 0)
		printf("%ld %d %s\n", now - table->time_start, table->idx, LOG_DIE);
	i = 0;
	if (table->times_eat > 0)
		while (i++ < table->philo_num)
			sem_post(table->s_end_eat);
	exit(1);
}
