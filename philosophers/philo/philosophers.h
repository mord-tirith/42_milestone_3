#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

/* Includes: */
# include <stdbool.h>
# include <pthread.h>

/* Types: */
typedef struct s_table
{
	int				meals;
	int				size;
	pthread_mutex_t	*forks;
}	t_table;

typedef struct s_philo
{
	int					id;
	int					tt_think;
	int					tt_eat;
	int					tt_sleep;
	int					tt_die;
	int					meals_eaten;
	int					l_fork;
	int					r_fork;
	long				last_meal;
	bool				alive;
	bool				done;
	pthread_t			thread;
	struct s_cave		*cave;
	pthread_mutex_t		philock;
}	t_philo;

typedef struct s_cave
{
	long			now;
	long			start;
	bool			finished;
	bool			finite;
	t_table			table;
	t_philo			*philos;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	cavelock;
}	t_cave;

/* Macros: */
# define NO_LIM -42
# define FOR_ERR "thread creation failed"
# define MUT_ERR "mutex creation failed"
# define MAL_ERR "internal malloc error"
# define ARG_ERR "size, tt_die, tt_eat, tt_sleep [, meal_count (optional)]"
# define VAL_ERR "arguments must be positive integers only"

/* Functions: */
int		ft_atoi(char *str);
int		ft_prepare_cave(t_cave *cave, int args[5]);
int		ft_handle_error(t_cave *cave, int error);
int		ft_start_thinking(t_cave *cave);
long	ft_clock(void);
void	ft_clean_cave(t_cave *cave);
void	ft_printer(t_cave *c, t_philo *p, char *msg);
void	*ft_routine(void *arg);
#endif
