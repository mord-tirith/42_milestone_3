/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thenriqu <thenriqu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 14:46:28 by thenriqu          #+#    #+#             */
/*   Updated: 2025/08/11 18:13:50 by thenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

/* Includes: */
# include <pthread.h>
# include <unistd.h>
/* Types: */

typedef struct s_table
{
	int				size;
	int				tt_die;
	int				tt_eat;
	int				tt_sleep;
	int				meal_count;
	int				finished;
	long			start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	printer_lock;
}	t_table;

typedef struct s_philo
{
	int				id;
	int				tt_think;
	int				left_fork;
	int				right_fork;
	int				meals_eaten;
	t_table			*table;
	pthread_t		thread;
	volatile int	alive;
	volatile int	finished;
	volatile long	last_meal;
	pthread_mutex_t	struct_lock;
}	t_philo;

typedef struct s_cave
{
	t_table	*table;
	t_philo	*philos;
}	t_cave;

/* Functions: */
int		ft_atoi(char *s);
int		ft_error_printer(t_cave *cave, int code);
void	ft_printer(t_philo *philo, const char *status);
long	ft_current_time(void);
void	ft_clean_cave(t_cave *cave);
void	*ft_routine(void *arg);
t_cave	*ft_fill_cave(int size, int tt_die, int tt_eat, int tt_sleep);

#endif
