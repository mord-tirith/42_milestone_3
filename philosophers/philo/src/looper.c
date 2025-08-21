
#include "philo.h"
#include <pthread.h>
#include <unistd.h>

static int	done_check(t_table *t)
{
	int	i;

	i = -1;
	while (++i < t->size)
	{
		pthread_mutex_lock(&t->philos[i].philock);
		if (t->philos[i].meal_count < t->servings)
		{
			pthread_mutex_unlock(&t->philos[i].philock);
			return (0);
		}
		pthread_mutex_unlock(&t->philos[i].philock);
	}
	pthread_mutex_lock(&t->end_lock);
	t->done = true;
	pthread_mutex_unlock(&t->end_lock);
	return (1);
}

static int	death_check(t_table *t)
{
	int	i;

	i = -1;
	while (++i < t->size)
	{
		pthread_mutex_lock(&t->philos[i].philock);
		if (ft_clock() - t->philos[i].last_meal >= t->tt_die)
		{
			t->philos[i].alive = false;
			pthread_mutex_lock(&t->end_lock);
			t->done = true;
			pthread_mutex_unlock(&t->end_lock);
			pthread_mutex_unlock(&t->philos[i].philock);
			ft_printer(DIE, "has died", &t->philos[i]);
			return (1);
		}
		pthread_mutex_unlock(&t->philos[i].philock);
	}
	return (0);
}

int	ft_death_watch(t_table *t)
{
	int		i;

	while (1)
	{
		if (death_check(t))
			break ;
		if (t->finite && done_check(t))
			break ;
		usleep(1000);
	}
	i = -1;
	while (++i < t->size)
		pthread_join(t->philos[i].thread, NULL);
	return (ft_cleanup(t));
}
