#ifndef PHILO_PROC_H
# define PHILO_PROC_H

# include <semaphore.h>
# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>
# include <stdlib.h>
# include <signal.h>
# include "errno.h"

# define LOG_FORK "has taken a fork"
# define LOG_EAT "is eating"
# define LOG_SLEEP "is sleeping"
# define LOG_THINK "is thinking"
# define LOG_DIE "died"

typedef struct s_table
{
	int			philo_num;
	long		time_die;
	long		time_eat;
	long		time_sleep;
	long		times_eat;
	long		time_start;
	int			flag_die;

	pid_t		*pid;
	pthread_t	tid;
	int			idx;
	long		p_time_eat;
	long		p_times_eat;

	sem_t		*s_forks;
	sem_t		*s_die;
	sem_t		*s_times;
	sem_t		*s_log;
	sem_t		*s_start_eat;
	sem_t		*s_end_eat;
}			t_table;

/* PROC.C */
void	get_proc(t_table *table);
void	parent_kill_proc(t_table *table, int philo_num);
void	get_thread_monitor(t_table *table);
void	*monitor_timeseat(void *data);

/* ROUTINE.C */
void	child_routine(t_table *table);
void	take_fork(t_table *table);
void	eat(t_table *table, int time_eat);
void	drop_fork(t_table *table, int time_sleep);

/* MONITOR.C */
void	*monitor(void *data);
void	monitor_starve(t_table *table);
int		is_philo_dead(t_table *table);
void	kill_philo_bonus(t_table *table, int kill_idx);

/* INIT.C = PHILO.H : init_table */
int		init_table(t_table *table, char *argv[]);
int		init_pid(pid_t **pid, int philo_num);
int		init_sem(t_table *table);

/* EXIT.C = PHILO_.H : errmsg */
int		exit_philo(t_table *table, int errno);
void	close_sem(t_table *table);
void	free_philo(t_table *table);
int		errmsg(int errno);

/* LIBFT.C = PHILO.H */
long	ft_atoi(const char *str);
void	*ft_memset(void *ptr, int c, size_t len);
void	*ft_calloc(size_t count, size_t size);
void	ft_putstr_fd(char *str, int fd);

/* UTILS.C = PHILO.H */
void	gettimeofday_milli(long *millisec);
void	usleep_milli(long millisec);
void	print_log(t_table *table, int philo_id, char *msg);

#endif