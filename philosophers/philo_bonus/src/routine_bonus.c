
#include "philo_bonus.h"
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void	*death_watch(void *arg)
{
	t_cave	*self;

	self = (t_cave *)arg;
	while (42)
	{
		if (ft_clock() - self->last_meal > self->tt_die)
		{
			ft_printer(self->id, DIE, "has died", self);
			exit(DIED);
		}
		if (self->servings <= 0 && self->finite)
			exit(FINI);
		usleep(self->tt_die * 100);
	}
	return (NULL);
}

void	ft_routine(t_cave *cave)
{
	pthread_t	watcher;

	cave->last_meal = ft_clock();
	pthread_create(&watcher, NULL, death_watch, cave);
	pthread_detach(watcher);
	while (!cave->done)
	{
		ft_printer(cave->id, THINK, "is thinking", cave);
		usleep((cave->id * 100) % (cave->tt_die / 2));
		sem_wait(cave->forks);
		ft_printer(cave->id, PICK, "has taken a fork", cave);
		sem_wait(cave->forks);
		ft_printer(cave->id, PICK, "has taken a fork", cave);
		cave->last_meal = ft_clock();
		ft_printer(cave->id, EAT, "is eating", cave);
		usleep(cave->tt_eat * 1000);
		if (cave->finite)
			cave->servings -= 1;
		sem_post(cave->forks);
		sem_post(cave->forks);
		ft_printer(cave->id, SLEEP, "is sleeping", cave);
		usleep(cave->tt_sleep * 1000);
	}
}
