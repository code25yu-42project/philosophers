#include "philo_thread.h"

int	main(int argc, char *argv[])
{
	t_table	table;

	if (argc != 5 & argc != 6)
		return (errmsg(INVALID_ARGV));
	if (init_table(&table, argv))
		return (errmsg(INVALID_ARGV));
	if (init_philos(&table.philos, &table))
		return (errmsg(MALLOC_FAILURE));
	if (init_forks(&table.forks, table.philo_num))
		return (exit_philo(&table, MALLOC_FAILURE));
	if (init_mutex(&table, table.philo_num))
		return (exit_philo(&table, EXTERNAL_FAILURE));
	if (get_thread(&table.philos, &table, table.philo_num))
		return (exit_philo(&table, EXTERNAL_FAILURE));
	join_thread(&table.philos, table.philo_num);
	exit_philo(&table, EXIT_SUCCESS);
	return (RETURN_SUCCESS);
}
