
#include "philosophers.h"
#include <pthread.h>
#include <stdlib.h>

static void	wash_forks(t_table *table)
{
	int	i;

	if (!table || !table->forks)
		return ;
	i = -1;
	while (++i < table->size)
		pthread_mutex_destroy(&table->forks[i]);
	free(table->forks);
}

void	ft_clean_cave(t_cave *cave)
{
	if (!cave)
		return ;
	if (cave->table)
	{
		wash_forks(cave->table);
		pthread_mutex_destroy(&cave->table->printer_lock);
		free(cave->table);
	}
	if (cave->philos)
		free(cave->philos);
	free(cave);
}