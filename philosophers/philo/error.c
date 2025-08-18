
#include "philo.h"
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

static void	erase_table(t_table *t)
{
	if (t->philos)
		free(t->philos);
	if (t->forks)
		free(t->forks);
	if (t->m_stats)
		free(t->m_stats);
	free(t);
	t = NULL;
}

static void	erase_mutex(t_table *t)
{
	int	i;

	i = -1;
	while (++i < t->size)
	{
		if (t->m_stats[i] == 0)
			pthread_mutex_destroy(&t->forks[i]);
		if (t->philos[i].m_stat == 0)
			pthread_mutex_destroy(&t->philos[i].philock);
	}
	if (t->print_stat == 0)
		pthread_mutex_destroy(&t->print_lock);
	if (t->end_stat == 0)
		pthread_mutex_destroy(&t->end_lock);
}

static int	clean_errors(int c, t_table *t)
{
	if (c == 3)
	{
		erase_table(t);
		printf("%s", MAL_ERR);
	}
	if (c == 4)
	{
		erase_mutex(t);
		erase_table(t);
		printf("%s", THR_ERR);
	}
	return (c);
}

int	ft_handle_error(int code, t_table *table)
{
	if (code != 1)
		printf("Error: ");
	if (table)
		return (clean_errors(code, table));
	if (code == 1)
		printf("Use: ./philosophers %s", ARG_ERR);
	if (code == 2)
		printf("%s", VAL_ERR);
	if (code == 3)
		printf("%s", MAL_ERR);
	return (code);
}
