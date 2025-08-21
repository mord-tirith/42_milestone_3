
#include "philo_bonus.h"
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

static void	safe_sleep(int id, int tt, t_cave *c, bool literal)
{
	if (!literal)
		tt *= 1000;
	while (tt > 0)
	{
		usleep(1000);
		if (ft_clock() - c->last_meal > c->tt_die)
		{
			ft_printer(id, DIE, "has died", c);
			exit(DIED);
		}
		tt -= 1000;
	}
}

static void	take_action(int i, int a, char *m, t_cave *c)
{
	long	now;

	now = ft_clock();
	if (now - c->last_meal > c->tt_die)
	{
		ft_printer(i, DIE, "has died", c);
		exit(DIED);
	}
	else
		ft_printer(i, a, m, c);
}

void	ft_routine(t_cave *cave, int id)
{
	cave->last_meal = ft_clock();
	while (!cave->done)
	{
		take_action(id, THINK, "is thinking", cave);
		usleep((id * 100) % (cave->tt_die / 2));
		safe_sleep(id, (id * 100) % (cave->tt_die / 2), cave, true);
		sem_wait(cave->forks);
		take_action(id, PICK, "has taken a fork", cave);
		sem_wait(cave->forks);
		take_action(id, PICK, "has taken a fork", cave);
		cave->last_meal = ft_clock();
		take_action(id, EAT, "is eating", cave);
		safe_sleep(id, cave->tt_eat, cave, false);
		sem_post(cave->forks);
		sem_post(cave->forks);
		if (cave->finite)
		{
			cave->servings -= 1;
			if (!cave->servings)
				exit(FINI);
		}
		take_action(id, SLEEP, "is sleeping", cave);
		safe_sleep(id, cave->tt_sleep, cave, false);
	}
}
