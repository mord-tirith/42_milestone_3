#include "philosophers.h"
#include <bits/pthreadtypes.h>
#include <limits.h>
#include <pthread.h>
#include <stdlib.h>


static void	set_philos(t_philo *philo, int size, int args[5], bool lim)
{
	static int	id;

	philo->id = ++id;
	philo->tt_die = args[1];
	philo->tt_eat = args[2];
	philo->tt_sleep = args[3];
	if (args[1] >= 32)
		philo->tt_think = ((id * 10) % (args[1] / 16));
	else
		philo->tt_think = ((id * 10) % size);
	philo->l_fork = id - 1;
	philo->r_fork = id % size;
	if (lim)
		philo->meals_eaten = 0;
	else
		philo->meals_eaten = INT_MIN;
	philo->alive = true;
	philo->done = false;
	philo->last_meal = LONG_MAX;
}

static int	set_table(t_table *t, int args[5], bool lim)
{
	t->forks = malloc(sizeof(pthread_mutex_t) * args[0]);
	if (!t->forks)
		return (0);
	t->size = args[0];
	if (lim)
		t->meals = args[4];
	else
		t->meals = NO_LIM;
	return (1);
}

static int	init_forks(t_cave *cave)
{
	int	i;

	i = -1;
	while (++i < cave->table.size)
	{
		if (pthread_mutex_init(&cave->table.forks[i], NULL))
			break ;
	}
	if (i != cave->table.size)
	{
		while (--i >= 0)
			pthread_mutex_destroy(&cave->table.forks[i]);
		i = -1;
		while (++i < cave->table.size)
			pthread_mutex_destroy(&cave->philos[i].philock);
		pthread_mutex_destroy(&cave->cavelock);
		pthread_mutex_destroy(&cave->print_lock);
		return (0);
	}
	return (1);
}

static int	init_locks(t_cave *cave)
{
	int	i;

	i = -1;
	while (++i < cave->table.size)
	{
		if (pthread_mutex_init(&cave->philos[i].philock, NULL))
			break ;
	}
	if (i != cave->table.size)
	{
		while (--i >= 0)
			pthread_mutex_destroy(&cave->philos[i].philock);
		return (0);
	}
	if (pthread_mutex_init(&cave->cavelock, NULL))
		return (0);
	if (pthread_mutex_init(&cave->print_lock, NULL))
	{
		pthread_mutex_destroy(&cave->cavelock);
		return (0);
	}
	return (init_forks(cave));
}

int	ft_prepare_cave(t_cave *cave, int *args)
{
	int	i;

	cave->philos = malloc(sizeof(t_philo) * args[0]);
	if (!cave->philos)
		return (1);
	if (!set_table(&cave->table, args, cave->finite))
	{
		free(cave->philos);
		return (1);
	}
	cave->finished = false;
	cave->table.size = args[0];
	i = -1;
	if (!init_locks(cave))
		return (2);
	while (++i < args[0])
	{
		set_philos(&cave->philos[i], args[0], args, cave->finite);
		cave->philos[i].cave = cave;
	}
	return (0);
}
