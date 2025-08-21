
#include "philo.h"
#include <stdlib.h>
#include <pthread.h>

static void	undo_mutexes(t_table *t)
{
	int	i;

	i = -1;
	while (++i < t->size)
	{
		if (t->philos[i].m_stat == 0)
			pthread_mutex_destroy(&t->philos[i].philock);
		if (t->m_stats[i] == 0)
			pthread_mutex_destroy(&t->forks[i]);
	}
	if (t->print_stat == 0)
		pthread_mutex_destroy(&t->print_lock);
	if (t->end_stat == 0)
		pthread_mutex_destroy(&t->end_lock);
}

static void	undo_mallocs(t_table *t)
{
	if (!t)
		return ;
	if (t->forks)
		free(t->forks);
	if (t->philos)
		free(t->philos);
	if (t->m_stats)
		free(t->m_stats);
	free(t);
}

int	ft_cleanup(t_table *t)
{
	undo_mutexes(t);
	undo_mallocs(t);
	return (0);
}
