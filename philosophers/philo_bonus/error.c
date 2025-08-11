
#include "philosophers_bonus.h"
#include <stdio.h>
#include <stdlib.h>


int	ft_print_error(t_cave *cave, int code)
{
	if (code == 1)
	{
		printf("Use: ./philo_bonus amount, time_to_die, time to eat, ");
		printf("time_to_sleep, meal_count (optional)\n");
	}
	else if (code == 2)
		printf("Error: arguments must be positive and numerical!\n");
	else if (code == 3)
		printf("Internal malloc/semaphore error\n");
	if (cave)
	{
		sem_close(cave->forks);
		sem_close(cave->printer);
		sem_close(cave->death_flag);
		sem_unlink(SEM_FORKS);
		sem_unlink(SEM_PRINT);
		sem_unlink(SEM_DEATH);
		free(cave->pids);
	}
	return (code);
}
