#include "philosophers.h"
#include <stdlib.h>
#include <stdio.h>

static void	clean_cave(t_cave *cave)
{
	if (cave)
	{
		if (cave->table)
		{
			if (cave->table->forks)
				free(cave->table->forks);
			free(cave->table);
		}
		if (cave->philos)
			free(cave->philos);
		free(cave);
		cave = NULL;
	}
}

static int	errors_with_clean(t_cave *cave, int code)
{
	clean_cave(cave);
	if (code == 3)
		printf("Error: even optional argument must be positive and numerical!\n");
	return (code);
}

int	ft_error_printer(t_cave *cave, int code)
{
	if (cave)
		return (errors_with_clean(cave, code));
	if (code == 1)
		printf("Use: ./philosophers amount, time_to_die, time_to_eat, time_to_sleep, [Meal Count (optional)]\n");
	else if (code == 2)
		printf("Error: malloc error\n");
	else if (code == 3)
		printf("Error: arguments must be positive and numerical!\n");
	return (code);
}