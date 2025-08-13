
#include "philosophers.h"
#include <limits.h>
#include <pthread.h>
#include <unistd.h>

static int	death_check(t_philo *philo)
{
	long	elapsed;

	pthread_mutex_lock(&philo->philock);
	if (!philo->alive || philo->done)
	{
		pthread_mutex_unlock(&philo->philock);
		return (1);
	}
	if (philo->last_meal == LONG_MAX)
		philo->last_meal = ft_clock();
	elapsed = ft_clock() - philo->last_meal;
	if (elapsed >= philo->tt_die)
	{
		ft_printer(philo->cave, philo, "has died");
		philo->alive = false;
		pthread_mutex_unlock(&philo->philock);
		return (1);
	}
	pthread_mutex_unlock(&philo->philock);
	return (0);
}

static int	take_action(char *s, t_philo *p, int time)
{
	if (death_check(p))
		return (0);
	ft_printer(p->cave, p, s);
	if (death_check(p))
		return (0);
	usleep(time * 1000);
	return (1);
}

static void	*lonely_death(t_philo *philo)
{
	bool	alive;

	alive = true;
	take_action("is thinking", philo, philo->tt_think);
	take_action("has taken a fork", philo, 0);
	while (alive)
		death_check(philo);
	return (NULL);
}

static void	meal_time(t_philo *p, t_cave *c)
{
	int	forks[2];

	forks[p->id % 2] = p->l_fork;
	forks[1 - (p->id % 2)] = p->r_fork;
	if (death_check(p))
		return ;
	pthread_mutex_lock(&c->table.forks[forks[0]]);
	if (death_check(p))
		return ((void)pthread_mutex_unlock(&c->table.forks[forks[0]]));
	if (!take_action("has taken a fork", p, 0))
		return ((void)pthread_mutex_unlock(&c->table.forks[forks[0]]));
	pthread_mutex_lock(&c->table.forks[forks[1]]);
	if (!take_action("has taken a fork", p, 0))
	{
		pthread_mutex_unlock(&c->table.forks[forks[0]]);
		return ((void)pthread_mutex_unlock(&c->table.forks[forks[1]]));
	}
	pthread_mutex_lock(&p->philock);
	p->last_meal = ft_clock();
	pthread_mutex_unlock(&p->philock);
	take_action("is eating", p, p->tt_eat);
	pthread_mutex_unlock(&c->table.forks[forks[0]]);
	pthread_mutex_unlock(&c->table.forks[forks[1]]);
}

void	*ft_routine(void *arg)
{
	t_philo *self;

	self = (t_philo *)arg;
	if (self->cave->table.size == 1)
		return (lonely_death(self));
	while (1)
	{
		pthread_mutex_lock(&self->cave->cavelock);
		if (self->cave->finished)
		{
			pthread_mutex_unlock(&self->cave->cavelock);
			break ;
		}
		pthread_mutex_unlock(&self->cave->cavelock);
		if (!take_action("is thinking", self, self->tt_think))
			break ;
		meal_time(self, self->cave);
		pthread_mutex_lock(&self->philock);
		self->meals_eaten += 1;
		pthread_mutex_unlock(&self->philock);
		if (!take_action("is sleeping", self, self->tt_sleep))
			break ;
	}
	return (NULL);
}
