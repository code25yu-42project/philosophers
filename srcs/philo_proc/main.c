#include "philo_proc.h"

int	main(int argc, char *argv[])
{
	t_table	table;

	if (argc != 5 & argc != 6)
		return (errmsg(INVALID_ARGV));
	if (init_table(&table, argv))
		return (errmsg(INVALID_ARGV));
	if (init_pid(&table.pid, table.philo_num))
		return (errmsg(MALLOC_FAILURE));
	if (init_sem(&table))
		exit_philo(&table, EXTERNAL_FAILURE);
	get_proc(&table);
	exit_philo(&table, EXIT_SUCCESS);
	return (0);
}
