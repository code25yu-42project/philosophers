#ifndef PHILO_THREAD_H
# define PHILO_THREAD_H

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>
# include <stdlib.h>
# include "errno.h"

# define LOG_FORK "has taken a fork"
# define LOG_EAT "is eating"
# define LOG_SLEEP "is sleeping"
# define LOG_THINK "is thinking"
# define LOG_DIE "died"

typedef struct s_table
{
	int				philo_num;
	long			time_die;
	long			time_eat;
	long			time_sleep;
	long			times_eat;
	long			time_start;
	int				flag_die;

	struct s_philo	*philos;

	pthread_mutex_t	*forks;
	pthread_mutex_t	m_die;
	pthread_mutex_t	m_times;
	pthread_mutex_t	m_log;
	pthread_mutex_t	m_pause;
}			t_table;

typedef struct s_philo
{
	pthread_t	tid;
	int			idx;
	long		time_eat;
	long		times_eat;
	int			lfork;
	int			rfork;
	t_table		*table;
}				t_philo;

/* THREAD.C */
int		get_thread(t_philo **philos, t_table *table, int philo_num);
void	join_thread(t_philo **philos, int philo_num);

/* ROUTINE.C */
void	*routine(void *data);
int		take_fork(t_philo *philo);
void	eat(t_philo *philo);
void	drop_fork(t_philo *philo);

/* MONITOR.C */
int		monitor(t_philo **philos, t_table *table);
int		monitor_timeseat(t_philo **philos, t_table *table);
int		monitor_starve(t_philo **philos, t_table *table);
int		is_philo_dead(t_table *table);
void	kill_philo(t_philo *philo, int kill_idx);

/* INIT.C = PHILO_BONUS.H : init_table */
int		init_table(t_table *table, char *argv[]);
int		init_philos(t_philo **philos, t_table *table);
int		init_forks(pthread_mutex_t **forks, int fork_num);
int		init_mutex(t_table *table, int fork_num);

/* EXIT.C = PHILO_BONUS.H : errmsg */
int		exit_philo(t_table *table, int errno);
void	destroy_mutex(t_table *table);
void	free_philo(t_table *table);
int		errmsg(int errno);

/* LIBFT.C = PHILO_BONUS.H */
long	ft_atoi(const char *str);
void	*ft_memset(void *ptr, int c, size_t len);
void	*ft_calloc(size_t count, size_t size);
void	ft_putstr_fd(char *str, int fd);

/* UTILS.C = PHILO_BONUS.H */
void	gettimeofday_milli(long *millisec);
void	usleep_milli(long millisec);
void	print_log(t_philo *philo, int philo_id, char *msg);

#endif
