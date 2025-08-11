/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thenriqu <thenriqu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 14:40:29 by thenriqu          #+#    #+#             */
/*   Updated: 2025/08/11 18:13:50 by thenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>

static int	philo_died(t_philo *philo)
{
	long	now;
	long	delta_time;

	now = ft_current_time();
	pthread_mutex_lock(&philo->struct_lock);
	delta_time = now - philo->last_meal;
	pthread_mutex_unlock(&philo->struct_lock);
	now -= philo->table->start_time;
	if (delta_time >= philo->table->tt_die && !philo->finished)
	{
		pthread_mutex_lock(&philo->table->printer_lock);
		ft_printer(philo, "died");
		pthread_mutex_unlock(&philo->table->printer_lock);
		philo->alive = 0;
		philo->table->finished = 1;
		return (1);
	}
	return (0);
}

static int	empty_storage(t_cave *cave)
{
	int	i;
	int	finished;

	i = -1;
	finished = 1;
	while (++i < cave->table->size)
	{
		pthread_mutex_lock(&cave->philos[i].struct_lock);
		if (!cave->philos[i].finished)
			finished = 0;
		pthread_mutex_unlock(&cave->philos[i].struct_lock);
	}
	return (finished);
}

void	ft_start_thinking(t_cave *cave)
{
	int	i;

	i = -1;
	while (++i < cave->table->size)
		pthread_create(&cave->philos[i].thread, NULL,
			ft_routine, &cave->philos[i]);
	while (!cave->table->finished)
	{
		i = -1;
		while (++i < cave->table->size)
		{
			if (philo_died(&cave->philos[i]))
				break ;
		}
		usleep(1000);
		if (empty_storage(cave))
			break ;
	}
	i = -1;
	while (++i < cave->table->size)
		pthread_join(cave->philos[i].thread, NULL);
	ft_clean_cave(cave);
}

static int	invalid_input(char **args, t_cave **dest)
{
	int		vars[5];

	vars[0] = ft_atoi(args[0]);
	vars[1] = ft_atoi(args[1]);
	vars[2] = ft_atoi(args[2]);
	vars[3] = ft_atoi(args[3]);
	if (!vars[0] || !vars[1] || !vars[2] || !vars[3])
		return (ft_error_printer(NULL, 3));
	*dest = ft_fill_cave(vars[0], vars[1], vars[2], vars[3]);
	if (!*dest)
		return (ft_error_printer(NULL, 2));
	if (args[4])
	{
		vars[4] = ft_atoi(args[4]);
		if (!vars[4])
			return (ft_error_printer(*dest, 3));
		(*dest)->table->meal_count = vars[4];
	}
	return (0);
}

int	main(int ac, char **av)
{
	int		status;
	t_cave	*cave;

	if (ac != 5 && ac != 6)
		return (ft_error_printer(NULL, 1));
	status = invalid_input(av + 1, &cave);
	if (status)
		return (status);
	ft_start_thinking(cave);
	return (0);
}
