
#include "philo_bonus.h"
#include <semaphore.h>
#include <unistd.h>

static void	clean_semaphores(t_cave *c)
{
	if (c->forks != SEM_FAILED)
		sem_close(c->forks);
	if (c->printer != SEM_FAILED)
		sem_close(c->printer);
	if (c->death_flag != SEM_FAILED)
		sem_close(c->death_flag);
	sem_unlink(FORKS_SEM);
	sem_unlink(PRINT_SEM);
	sem_unlink(DEATH_SEM);
}

static int	clean_errors(int code, t_cave *cave)
{
	clean_semaphores(cave);
	if (code == 3)
		write(2, SEM_ERR, sizeof(SEM_ERR) - 1);
	if (code == 4)
		write(2, MAL_ERR, sizeof(MAL_ERR) - 1);
	return (code);
}

int	ft_handle_error(int code, t_cave *cave)
{
	if (code != 1)
		write(2, "Error: ", sizeof("Error: ") - 1);
	if (cave)
		return (clean_errors(code, cave));
	if (code == 1)
	{
		write(2, "Use: ./philosophers_bonus ", 26);
		write(2, ARG_ERR, sizeof(ARG_ERR) - 1);
	}
	if (code == 2)
		write(2, VAL_ERR, sizeof(VAL_ERR) - 1);
	return (code);
}
