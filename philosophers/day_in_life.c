/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   day_in_life.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thenriqu <thenriqu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 14:39:15 by thenriqu          #+#    #+#             */
/*   Updated: 2025/08/11 14:39:18 by thenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
static void	pick_forks(int id, int f_left, int f_right, int res[2])
{
	res[id % 2] = f_left;
	res[!(id % 2)] = f_right;
}
static void	eat(t_philo *philo)
{
	int		f[2];

	pick_forks(philo->id, philo->left_fork, philo->right_fork, f);
	if (!philo->alive || philo->table->finished)
		return ;
	pthread_mutex_lock(&philo->table->forks[f[0]]);
	if (!philo->alive || philo->table->finished)
		return ((void)pthread_mutex_unlock(&philo->table->forks[f[0]]));
	printer(philo, "picking up a fork");
	if (!philo->alive || philo->table->finished || f[0] == f[1])
		return ((void)pthread_mutex_unlock(&philo->table->forks[f[0]]));
	pthread_mutex_lock(&philo->table->forks[f[1]]);
	if (!philo->alive || philo->table->finished)
	{
		pthread_mutex_unlock(&philo->table->forks[f[0]]);
		return ((void)pthread_mutex_unlock(&philo->table->forks[f[1]]));
	}
	printer(philo, "picking up a fork");
	philo->last_meal = ft_current_time();
	printer(philo, "eating");
	usleep(philo->table->tt_eat * 1000);
	philo->meals_eaten += 1;
	pthread_mutex_unlock(&philo->table->forks[f[0]]);
	pthread_mutex_unlock(&philo->table->forks[f[1]]);
}
static int	finished(t_philo *philo)
{
	if (philo->table->meal_count == -1)
		return (0);
	if (philo->table->meal_count <= philo->meals_eaten)
	{
		philo->finished = 1;
		return (1);
	}
	return (0);
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
		if (!philo->alive || philo->table->finished || !philo->meals_eaten)
			break ;
		if (finished(philo))
		{
			printer(philo, "finished");
			break ;
		}
		printer(philo, "sleeping");
		if (!philo->alive || philo->table->finished)
			break ;
		usleep(philo->table->tt_sleep * 1000);
	}
	return (NULL);
}

