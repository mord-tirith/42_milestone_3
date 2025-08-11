#include "philosophers.h"
#include <stdlib.h>

static int	boot_table(t_table *table, int size)
{
	int	i;

	table->size = size;
	table->meal_count = -1;
	table->finished = 0;
	table->start_time = ft_current_time();
	table->forks = malloc(sizeof(pthread_mutex_t) * size);
	if (!table->forks)
		return (0);
	i = -1;
	while (++i < size)
		pthread_mutex_init(&table->forks[i], NULL);
	pthread_mutex_init(&table->printer_lock, NULL);
	return (1);
}

static int	boot_philos(t_philo **philos, t_table *table)
{
	int	i;

	*philos = malloc(sizeof(t_philo) * table->size);
	if (!*philos)
		return (0);
	i = -1;
	while (++i < table->size)
	{
		(*philos)[i].id = i + 1;
		(*philos)[i].alive = 1;
		(*philos)[i].finished = 0;
		(*philos)[i].tt_think = ((i * 10) % (table->tt_die / 16)) * 100;
		(*philos)[i].meals_eaten = 0;
		(*philos)[i].last_meal = table->start_time;
		(*philos)[i].left_fork = i;
		(*philos)[i].right_fork = (*philos)[i].id % table->size;
		(*philos)[i].table = table;
	}
	return (1);
}

static t_cave	*clean_return(t_cave *cave)
{
	if (cave)
	{
		if (cave->table)
		{
			free(cave->table->forks);
			free(cave->table);
		}
		free(cave);
	}
	return (NULL);
}

t_cave	*ft_fill_cave(int size, int tt_die, int tt_eat, int tt_sleep)
{
	t_cave	*new_cave;

	new_cave = malloc(sizeof(t_cave));
	if (!new_cave)
		return (NULL);
	new_cave->table = malloc(sizeof(t_table));
	if (!new_cave->table)
		return (clean_return(new_cave));
	if (!boot_table(new_cave->table, size))
		return (clean_return(new_cave));
	new_cave->table->tt_die = tt_die;
	new_cave->table->tt_eat = tt_eat;
	new_cave->table->tt_sleep = tt_sleep;
	if (!boot_philos(&(new_cave->philos), new_cave->table))
		return (clean_return(new_cave));
	return (new_cave);
}

