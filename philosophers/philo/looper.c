
#include "philosophers.h"
#include <pthread.h>
#include <unistd.h>

static int	meal_over(t_cave *cave)
{
	int	i;

	i = -1;
	while (++i < cave->table.size)
	{
		pthread_mutex_lock(&cave->philos[i].philock);
		if (!cave->philos[i].done)
		{
			pthread_mutex_unlock(&cave->philos[i].philock);
			return (0);
		}
		pthread_mutex_unlock(&cave->philos[i].philock);
	}
	return (1);
}

static int	end_check(t_cave *cave, t_philo *philo)
{
	int	ret;

	ret = 0;
	pthread_mutex_lock(&philo->philock);
	if (!philo->alive)
		ret = 1;
	if (cave->table.meals != NO_LIM)
	{
		if (philo->meals_eaten >= cave->table.meals)
			philo->done = true;
	}
	pthread_mutex_unlock(&philo->philock);
	if (ret)
	{
		pthread_mutex_lock(&cave->cavelock);
		cave->finished = true;
		pthread_mutex_unlock(&cave->cavelock);
	}
	return (ret);
}

static int	boot_threads(t_cave *cave)
{
	int	i;
	int	j;
	int	lim;

	i = -1;
	lim = cave->table.size;
	cave->start = ft_clock();
	while (++i < lim)
	{
		if (pthread_create(&cave->philos[i].thread, NULL,
			ft_routine, &cave->philos[i]))
			break ;
	}
	if (i != lim)
	{
		j = -1;
		while (++j < i)
			pthread_join(cave->philos[j].thread, NULL);
		return (0);
	}
	return (1);
}

int	ft_start_thinking(t_cave *cave)
{
	int		i;
	bool	run;

	i = -1;
	run = true;
	if (!boot_threads(cave))
		return (0);
	while (run)
	{
		i = -1;
		while (++i < cave->table.size)
		{
			if (end_check(cave, &cave->philos[i]))
				run = false;
		}
		if (meal_over(cave))
			run = false;
		usleep(1000);
	}
	i = -1;
	while (++i < cave->table.size)
		pthread_join(cave->philos[i].thread, NULL);
	ft_clean_cave(cave);
	return (1);
}
