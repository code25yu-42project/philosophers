#include "philo_thread.h"

void	gettimeofday_milli(long *millisec)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	*millisec = time.tv_sec * 1000 + time.tv_usec / 1000;
}

void	usleep_milli(long millisec)
{
	long	start;
	long	now;

	gettimeofday_milli(&start);
	usleep(millisec * 1000 * 0.5);
	while (1)
	{	
		usleep(500);
		gettimeofday_milli(&now);
		if (now - start >= millisec)
			return ;
	}
}

void	print_log(t_philo *philo, int philo_id, char *msg)
{
	long	now;

	pthread_mutex_lock(&philo->table->m_log);
	gettimeofday_milli(&now);
	if (!is_philo_dead(philo->table))
	{	
		printf("%ld %d %s\n", \
			now - philo->table->time_start, (int)philo_id, msg);
	}
	pthread_mutex_unlock(&philo->table->m_log);
}
