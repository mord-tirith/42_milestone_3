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
	volatile long	last_meal;
}	t_philo;

typedef struct s_cave
{
	t_table	*table;
	t_philo	*philos;
}	t_cave;

/* Macros: */

/* Functions: */
int		ft_atoi(char *s);
int		ft_error_printer(t_cave *cave, int code);
void	*ft_routine(void *arg);
long	ft_current_time(void);
t_cave	*ft_fill_cave(int size, int tt_die, int tt_eat, int tt_sleep);

#endif