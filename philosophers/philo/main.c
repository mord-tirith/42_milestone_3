
#include "philosophers.h"
#include <stdio.h>
#include <stdlib.h>

static t_cave	*dig_cave(bool finite)
{
	t_cave	*new_cave;

	new_cave = malloc(sizeof(t_cave));
	if (!new_cave)
		return (NULL);
	new_cave->finite = finite;
	new_cave->table.forks = NULL;
	new_cave->philos = NULL;
	return (new_cave);
}

static int valid_input(int dest[5], bool finite)
{
	int i;

	i = -1;
	while (++i < 4)
	{
		if (!dest[i])
			return (0);
	}
	if (finite && !dest[4])
		return (0);
	return (1);
}

static int	kickstart(t_cave *cave, int args[5])
{
	int	status;

	status = ft_prepare_cave(cave, args);
	if (status == 1)
		return (ft_handle_error(cave, 2));
	if (status == 2)
		return (ft_handle_error(cave, 3));
	if (!ft_start_thinking(cave))
		return (ft_handle_error(cave, 4));
	return (0);
}

int	main(int ac, char **av)
{
	int		i;
	int		args[5];
	t_cave	*cave;

	if (ac != 5 && ac != 6)
	{
		printf("Use: %s %s\n", av[0], ARG_ERR);
		return (1);
	}
	i = -1;
	av++;
	while (av[++i])
		args[i] = ft_atoi(av[i]);
	if (ac == 5)
		cave = dig_cave(false);
	else
		cave = dig_cave(true);
	if (!cave)
		return (ft_handle_error(NULL, 2));
	if (!valid_input(args, cave->finite))
		return (ft_handle_error(cave, 4));
	return (kickstart(cave, args));
}
