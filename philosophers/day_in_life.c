#include "philosophers.h"
#include <sys/time.h>
#include <stdio.h>

static void	printer(t_philo *philo, const char *status)
{
	long	time_now;

	pthread_mutex_lock(&philo->table->printer_lock);
	time_now = ft_current_time() - philo->table->start_time;
	printf("%ld: Philosopher %d is %s\n", time_now, philo->id, status);
	pthread_mutex_unlock(&philo->table->printer_lock);
}

static void	pick_forks(int id, int f_left, int f_right, int res[3])
{
	if (id % 2)
	{
		res[1] = f_right;
		res[2] = f_left;
	}
	else
	{
		res[1] = f_left;
		res[2] = f_right;
	}
}

static void	eat(t_philo *philo)
{
	int		f_vars[3];
	char	string[64];

	f_vars[0] = philo->table->size;
	pick_forks(philo->id, philo->left_fork, philo->right_fork, f_vars);
	if (!philo->alive || philo->table->finished)
		return ;
	pthread_mutex_lock(&philo->table->forks[f_vars[1]]);
	if (!philo->alive || philo->table->finished)
		return ((void)pthread_mutex_unlock(&philo->table->forks[f_vars[1]]));
	sprintf(string, "taking fork %d", f_vars[1]);
	printer(philo, string);
	if (!philo->alive || philo->table->finished)
		return ;
	pthread_mutex_lock(&philo->table->forks[f_vars[2]]);
	if (!philo->alive || philo->table->finished)
	{
		pthread_mutex_unlock(&philo->table->forks[f_vars[1]]);
		return ((void)pthread_mutex_unlock(&philo->table->forks[f_vars[2]]));
	}
	sprintf(string, "taking fork %d", f_vars[2]);
	printer(philo, string);
	philo->last_meal = ft_current_time();
	printer(philo, "eating");
	usleep(philo->table->tt_eat * 1000);
	philo->meals_eaten += 1;
	pthread_mutex_unlock(&philo->table->forks[f_vars[1]]);
	pthread_mutex_unlock(&philo->table->forks[f_vars[2]]);
}

void	*ft_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (philo->alive && !philo->table->finished)
	{
		if (!philo->alive || philo->table->finished)
			break ;
		printer(philo, "thinking");
		usleep(philo->tt_think);
		if (!philo->alive || philo->table->finished)
			break ;
		eat(philo);
		if (!philo->alive || philo->table->finished)
			break ;
		printer(philo, "sleeping");
		if (!philo->alive || philo->table->finished)
			break ;
		usleep(philo->table->tt_sleep * 1000);
	}
	return (NULL);
}

