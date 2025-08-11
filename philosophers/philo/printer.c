/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thenriqu <thenriqu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 17:43:36 by thenriqu          #+#    #+#             */
/*   Updated: 2025/08/11 17:47:30 by thenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <pthread.h>
#include <stdio.h>

void	ft_printer(t_philo *philo, const char *status)
{
	long	time_now;

	pthread_mutex_lock(&philo->table->printer_lock);
	time_now = ft_current_time() - philo->table->start_time;
	printf("%ld %d %s\n", time_now, philo->id, status);
	pthread_mutex_unlock(&philo->table->printer_lock);
}
