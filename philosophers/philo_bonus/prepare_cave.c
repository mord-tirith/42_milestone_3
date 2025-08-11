
#include "philosophers_bonus.h"
#include <fcntl.h>
#include <stdlib.h>

static int	set_semaphores(t_cave *cave)
{
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_PRINT);
	sem_unlink(SEM_DEATH);
	cave->forks = sem_open(SEM_FORKS, O_CREAT, 0644, cave->size);
	if (cave->forks == SEM_FAILED)
		return (0);
	cave->printer = sem_open(SEM_PRINT, O_CREAT, 0644, 1);
	if (cave->printer == SEM_FAILED)
	{
		sem_close(cave->forks);
		sem_unlink(SEM_FORKS);
		return (0);
	}
	cave->death_flag = sem_open(SEM_DEATH, O_CREAT, 0644, 0);
	if (cave->death_flag != SEM_FAILED)
		return (1);
	sem_close(cave->forks);
	sem_close(cave->printer);
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_PRINT);
	return (0);
}

static void	set_cave(t_cave *cave, int die, int eat, int sleep)
{
	cave->tt_die = die;
	cave->tt_eat = eat;
	cave->tt_sleep = sleep;
	cave->finished = 0;
	cave->meal_count = -1;
}

void	ft_prepare_cave(t_cave *cave, int tt_die, int tt_eat, int tt_sleep)
{
	cave->pids = malloc(sizeof(pid_t) * cave->size);
	if (!cave->pids)
		return ;
	set_cave(cave, tt_die, tt_eat, tt_sleep);
	if (!set_semaphores(cave))
	{
		free(cave->pids);
		cave->pids = NULL;
		return ;
	}
	cave->start_time = ft_get_time();
}

