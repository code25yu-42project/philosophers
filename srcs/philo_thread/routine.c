#include "philo_thread.h"

void	*routine(void *data)
{
	t_philo	*philo;
	int		philo_num;

	philo = (t_philo *)data;
	philo_num = philo->table->philo_num;
	pthread_mutex_lock(&philo->table->m_pause);
	pthread_mutex_unlock(&philo->table->m_pause);
	if (philo->idx % 2 == 0 \
	|| (philo_num % 2 && philo->idx > 1 && philo->idx == philo_num))
	{
		print_log(philo, philo->idx, LOG_SLEEP);
		usleep_milli(philo->table->time_sleep);
		print_log(philo, philo->idx, LOG_THINK);
	}
	while (!is_philo_dead(philo->table))
	{	
		if (take_fork(philo))
			return (0);
		eat(philo);
		drop_fork(philo);
	}
	return (0);
}

int	take_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->forks[philo->lfork]);
	print_log(philo, philo->idx, LOG_FORK);
	if (philo->table->philo_num == 1)
	{
		pthread_mutex_unlock(&philo->table->forks[philo->lfork]);
		return (RETURN_FAILURE);
	}
	pthread_mutex_lock(&philo->table->forks[philo->rfork]);
	print_log(philo, philo->idx, LOG_FORK);
	return (RETURN_SUCCESS);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->m_times);
	gettimeofday_milli(&philo->time_eat);
	pthread_mutex_unlock(&philo->table->m_times);
	print_log(philo, philo->idx, LOG_EAT);
	usleep_milli(philo->table->time_eat);
	pthread_mutex_lock(&philo->table->m_times);
	philo->times_eat += 1;
	pthread_mutex_unlock(&philo->table->m_times);
}

void	drop_fork(t_philo *philo)
{
	pthread_mutex_unlock(&philo->table->forks[philo->lfork]);
	pthread_mutex_unlock(&philo->table->forks[philo->rfork]);
	print_log(philo, philo->idx, LOG_SLEEP);
	usleep_milli(philo->table->time_sleep);
	print_log(philo, philo->idx, LOG_THINK);
}
