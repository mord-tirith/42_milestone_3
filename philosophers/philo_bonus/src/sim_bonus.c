
#include "philo_bonus.h"
#include <semaphore.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

static void	monitor(t_cave *cave)
{
	int		i;
	int		status;
	int		done;
	pid_t	tempid;

	done = 0;
	while (done < cave->size)
	{
		tempid = waitpid(-1, &status, 0);
		if (tempid <= 0)
			continue ;
		if (WIFEXITED(status))
		{
			status = WEXITSTATUS(status);
			if (status == DIED)
			{
				i = -1;
				while (++i < cave->size)
					kill(cave->pids[i], SIGTERM);
				break ;
			}
			else if (status == FINI)
				done++;
		}
	}
}

int	ft_boot_sim(t_cave *cave)
{
	int	i;

	i = -1;
	cave->start = ft_clock();
	while (++i < cave->size)
	{
		cave->pids[i] = fork();
		if (cave->pids[i] < 0)
			return (ft_handle_error(5, cave));
		if (cave->pids[i] == 0)
		{
			cave->id = i + 1;
			ft_routine(cave);
			exit(IMPO);
		}
	}
	monitor(cave);
	return (ft_cleanup(cave));
}
