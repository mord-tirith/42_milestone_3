#ifndef PHILO_H
# define PHILO_H

/* Includes: */
# include <pthread.h>
# include <stdbool.h>

/* Types: */

typedef struct s_table
{
	int				size;
	int				tt_die;
	int				tt_eat;
	int				tt_sleep;
	int				servings;
	int				*m_stats;
	int				end_stat;
	int				print_stat;
	bool			done;
	bool			finite;
	long			start;
	struct s_philo	*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	end_lock;
}	t_table;

typedef struct s_philo
{
	int				id;
	int				meal_count;
	int				m_stat;
	int				t_stat;
	int				tt_think;
	long			last_meal;
	bool			alive;
	t_table			*table;
	pthread_t		thread;
	pthread_mutex_t	philock;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
}	t_philo;

typedef enum e_actions
{
	THINK = 33,
	PICK = 33,
	EAT = 32,
	SLEEP = 33,
	DIE = 31
}	t_actions;

/* Macros: */

# define ARG_ERR "N, death_time, meal_time, sleep_time [, N_meals]\n"
# define VAL_ERR "All arguments must be positive integers\n"
# define MAL_ERR "Malloc failed please try again\n"
# define THR_ERR "Thread/Mutex creation failed, please try again\n"


/* Functions: */
int		ft_atopi(char *str);
int		ft_cleanup(t_table *t);
int		ft_death_watch(t_table *table);
int		ft_handle_error(int code, t_table *table);
int		ft_boot_sim(t_table *table);
long	ft_clock(void);
void	ft_printer(int action, char *msg, t_philo *philo);
void	*ft_routine(void *arg);

#endif
