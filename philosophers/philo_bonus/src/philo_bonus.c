
#include "philo_bonus.h"
#include <fcntl.h>
#include <semaphore.h>
#include <stdlib.h>
#include <sys/types.h>

static int	parse_pids(t_cave *cave)
{
	cave->pids = malloc(sizeof(pid_t) * cave->size);
	if (!cave->pids)
		return (0);
	return (1);
}

static int	parse_sems(t_cave *cave)
{
	sem_unlink(FORKS_SEM);
	sem_unlink(PRINT_SEM);
	sem_unlink(DEATH_SEM);
	cave->forks = sem_open(FORKS_SEM, O_CREAT, 0644, cave->size);
	cave->printer = sem_open(PRINT_SEM, O_CREAT, 0644, 1);
	cave->death_flag = sem_open(DEATH_SEM, O_CREAT, 0644, 0);
	if (cave->forks == SEM_FAILED || cave->printer == SEM_FAILED
		|| cave->death_flag == SEM_FAILED)
		return (0);
	return (1);
}

static int	parse_args(char **av, t_cave *cave)
{
	cave->size = ft_atopi(av[0]);
	cave->tt_die = ft_atopi(av[1]);
	cave->tt_eat = ft_atopi(av[2]);
	cave->tt_sleep = ft_atopi(av[3]);
	if (!cave->size || !cave->tt_die || !cave->tt_eat || !cave->tt_sleep)
		return (0);
	cave->done = false;
	cave->finite = false;
	cave->servings = -1;
	if (!av[4])
		return (1);
	cave->servings = ft_atopi(av[4]);
	if (!cave->servings)
		return (0);
	cave->finite = true;
	return (1);
}

#include <stdio.h>

int	main(int ac, char **av)
{
	static t_cave	cave;

	if (ac != 5 && ac != 6)
		return (ft_handle_error(1, NULL));
	if (!parse_args(av + 1, &cave))
		return (ft_handle_error(2, NULL));
	if (!parse_sems(&cave))
		return (ft_handle_error(3, &cave));
	if (!parse_pids(&cave))
		return (ft_handle_error(4, &cave));
	ft_boot_sim(&cave);
}
