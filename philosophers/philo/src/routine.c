
#include "philo.h"
#include <pthread.h>
#include <unistd.h>

static int	take_action(int tt, int code, char *m, t_philo *p)
{
	bool	still_alive;

	pthread_mutex_lock(&p->table->end_lock);
	if (p->table->done)
	{
		pthread_mutex_unlock(&p->table->end_lock);
		return (0);
	}
	pthread_mutex_unlock(&p->table->end_lock);
	ft_printer(code, m, p);
	usleep(1000L * (long)tt);
	pthread_mutex_lock(&p->philock);
	still_alive = p->alive;
	pthread_mutex_unlock(&p->philock);
	if (!still_alive)
		return (0);
	return (1);
}

static int	meal_time(t_philo *p)
{
	int	flag;

	pthread_mutex_lock(p->l_fork);
	if (!take_action(0, PICK, "has taken a fork", p))
	{
		pthread_mutex_unlock(p->l_fork);
		return (0);
	}
	pthread_mutex_lock(p->r_fork);
	if (!take_action(0, PICK, "has taken a fork", p))
	{
		pthread_mutex_unlock(p->l_fork);
		pthread_mutex_unlock(p->r_fork);
		return (0);
	}
	pthread_mutex_lock(&p->philock);
	p->last_meal = ft_clock();
	if (p->table->finite)
		p->meal_count += 1;
	pthread_mutex_unlock(&p->philock);
	flag = take_action(p->table->tt_eat, EAT, "is eating", p);
	pthread_mutex_unlock(p->l_fork);
	pthread_mutex_unlock(p->r_fork);
	return (flag);
}

static void	*lonely_death(t_philo *p)
{
	take_action(p->tt_think, THINK, "is thinking", p);
	take_action(0, PICK, "has taken a fork", p);
	usleep(p->table->tt_die);
	return (NULL);
}

void	*ft_routine(void *arg)
{
	t_philo	*self;

	self = (t_philo *)arg;
	if (self->table->size == 1)
		return (lonely_death(self));
	while (1)
	{
		if (!take_action(self->tt_think, THINK, "is thinking", self))
			break ;
		if (!meal_time(self))
			break ;
		if (!take_action(self->table->tt_sleep, SLEEP, "is sleeping", self))
			break ;
	}
	return (NULL);
}
