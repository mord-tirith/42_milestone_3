#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

/* Includes: */
# include <stdbool.h>
# include <semaphore.h>
# include <sys/types.h>

/* Types: */

typedef enum e_colors
{
	THINK = 33,
	PICK = 33,
	SLEEP = 33,
	EAT = 32,
	DIE = 31
}	t_colors;

typedef struct s_cave
{
	int		size;
	int		tt_die;
	int		tt_eat;
	int		tt_sleep;
	int		servings;
	long	start;
	long	last_meal;
	bool	finite;
	bool	done;
	sem_t	*forks;
	sem_t	*printer;
	sem_t	*death_flag;
	pid_t	*pids;
}	t_cave;

/* Macros: */
# define IMPO 0 << 0
# define DIED 1 << 0
# define FINI 1 << 1
# define FORKS_SEM "/forks"
# define PRINT_SEM "/printer"
# define DEATH_SEM "/death_flag"
# define ARG_ERR "N, death_time, meal_time, sleep_time [, N_meals]\n"
# define VAL_ERR "All arguments must be positive INTs\n"
# define SEM_ERR "Error creating semaphore\n"
# define MAL_ERR "Internal error using malloc\n"


/* Functions: */

int		ft_atopi(char *str);
int		ft_cleanup(t_cave *cave);
int		ft_boot_sim(t_cave *cave);
int		ft_handle_error(int code, t_cave *cave);
long	ft_clock(void);
void	ft_printer(int id, int action, char *msg, t_cave *cave);
void	ft_routine(t_cave *cave, int id);
#endif
