
#include "philosophers.h"
#include <pthread.h>
#include <stdlib.h>

static void	wash_forks(t_table *table)
{
	int	i;

	if (!table->forks)
		return ;
	i = -1;
	while (++i < table->size)
		pthread_mutex_destroy(&table->forks[i]);
	free(table->forks);
}

void	ft_clean_cave(t_cave *cave)
{
	int	i;
	int	lim;

	if (!cave)
		return ;
	i = -1;
	lim = cave->table.size;
	wash_forks(&cave->table);
	if (cave->philos)
	{
		while (++i < lim)
			pthread_mutex_destroy(&cave->philos[i].philock);
		free(cave->philos);
	}
	pthread_mutex_destroy(&cave->cavelock);
	pthread_mutex_destroy(&cave->print_lock);
	free(cave);
}
