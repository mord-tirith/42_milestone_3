/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thenriqu <thenriqu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 14:39:27 by thenriqu          #+#    #+#             */
/*   Updated: 2025/08/11 18:13:50 by thenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdlib.h>

static void	wash_forks(t_table *table)
{
	int	i;

	if (!table || !table->forks)
		return ;
	i = -1;
	while (++i < table->size)
		pthread_mutex_destroy(&table->forks[i]);
	free(table->forks);
}

void	ft_clean_cave(t_cave *cave)
{
	int	i;
	int	lim;

	if (!cave)
		return ;
	i = -1;
	lim = cave->table->size;
	if (cave->table)
	{
		wash_forks(cave->table);
		pthread_mutex_destroy(&cave->table->printer_lock);
		free(cave->table);
	}
	if (cave->philos)
	{
		while (++i < lim)
			pthread_mutex_destroy(&cave->philos[i].struct_lock);
		free(cave->philos);
	}
	free(cave);
}
