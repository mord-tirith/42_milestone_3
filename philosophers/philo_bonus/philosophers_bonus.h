
#ifndef PHILOSOPHERS_BONUS_H
# define PHILOSOPHERS_BONUS_H

/* Includes: */
#include <semaphore.h>
#include <sys/types.h>

/* Types: */
typedef struct s_cave
{
	int		size;
	int		tt_die;
	int		tt_eat;
	int		tt_sleep;
	int		finished;
	int		meal_count;
	long	last_meal;
	long	start_time;
	sem_t	*forks;
	sem_t	*printer;
	sem_t	*death_flag;
	pid_t	*pids;
}	t_cave;

/* Macros: */

# define SEM_FORKS "/forks"
# define SEM_PRINT "/printer"
# define SEM_DEATH "/death_flag"

/* Functions: */
int		ft_atoi(char *str);
int		ft_print_error(t_cave *cave, int code);
long	ft_get_time(void);
void	ft_prepare_cave(t_cave *cave, int tt_die, int tt_eat, int tt_sleep);


#endif
