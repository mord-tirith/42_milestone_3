
#include "philo.h"
#include <pthread.h>
#include <stdlib.h>

static int	init_mutex(t_table *t, int n)
{
	int	i;

	i = -1;
	while (++i < n)
	{
		t->m_stats[i] = pthread_mutex_init(&t->forks[i], NULL);
		t->philos[i].m_stat = pthread_mutex_init(&t->philos[i].philock, NULL);
	}
	t->print_stat = pthread_mutex_init(&t->print_lock, NULL);
	t->end_stat = pthread_mutex_init(&t->end_lock, NULL);
	if (t->print_stat || t->end_stat)
		return (0);
	i = -1;
	while (++i < n)
	{
		if (t->m_stats[i] != 0 || t->philos[i].m_stat != 0)
			return (0);
	}
	return (1);
}

static int	init(int ac, int args[5], t_table *t)
{
	t->size = args[0];
	t->tt_die = args[1];
	t->tt_eat = args[2];
	t->tt_sleep = args[3];
	if (ac == 6)
	{
		t->finite = true;
		t->servings = args[4];
	}
	else
	{
		t->finite = false;
		t->servings = -1;
	}
	t->done = false;
	return (init_mutex(t, args[0]));
}

static t_table	*set_t(int n)
{
	t_table *new_t;

	new_t = malloc(sizeof(t_table));
	if (!new_t)
		return (NULL);
	new_t->philos = NULL;
	new_t->forks = NULL;
	new_t->m_stats = NULL;
	new_t->philos = malloc(sizeof(t_philo) * n);
	new_t->forks = malloc(sizeof(pthread_mutex_t) * n);
	new_t->m_stats = malloc(sizeof(int) * n);
	return (new_t);
}

int main(int ac, char **av)
{
	int		i;
	int		args[5];
	t_table	*table;

	if (ac != 5 && ac != 6)
		return (ft_handle_error(1, NULL));
	i = 0;
	while (++i < ac)
		args[i - 1] = ft_atopi(av[i]);
	i = -1;
	while (++i < ac - 1)
	{
		if (args[i] == 0)
			return (ft_handle_error(2, NULL));
	}
	table = set_t(args[0]);
	if (!table || !table->philos || !table->forks || !table->m_stats)
		return (ft_handle_error(3, table));
	if (!init(ac, args, table))
		return (ft_handle_error(4, table));
	return (ft_boot_sim(table));
}
