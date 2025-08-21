
#include "philo.h"
#include <pthread.h>


static void	make_philo(int i, t_philo *p, t_table *t)
{
	p->id = i + 1;
	p->meal_count = 0;
	p->alive = true;
	p->table = t;
	p->l_fork = &p->table->forks[p->id % t->size];
	p->r_fork = &p->table->forks[p->id - 1];
	if (i % 2)
	{
		p->l_fork = &p->table->forks[p->id - 1];
		p->r_fork = &p->table->forks[p->id % t->size];
	}
	p->tt_think = p->id % 3;
	p->last_meal = ft_clock();
}

static int	broken_thread(t_table *t)
{
	int	i;

	i = -1;
	while (++i < t->size)
	{
		if (t->philos[i].t_stat == 0)
			pthread_join(t->philos[i].thread, NULL);
	}
	return (ft_handle_error(4, t));
}

int	ft_boot_sim(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->size)
		make_philo(i, &table->philos[i], table);
	i = -1;
	table->start = ft_clock();
	while (++i < table->size)
		table->philos[i].t_stat = pthread_create(&table->philos[i].thread, NULL, ft_routine, &table->philos[i]);
	i = -1;
	while (++i < table->size)
	{
		if (table->philos[i].t_stat != 0)
			return (broken_thread(table));
	}
	return (ft_death_watch(table));
}
