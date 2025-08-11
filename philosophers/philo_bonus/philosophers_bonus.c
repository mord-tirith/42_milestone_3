
#include "philosophers_bonus.h"
#include <stdio.h>

static int	invalid_input(t_cave *cave, char **args)
{
	int	vars[5];

	vars[0] = ft_atoi(args[0]);
	vars[1] = ft_atoi(args[1]);
	vars[2] = ft_atoi(args[2]);
	vars[3] = ft_atoi(args[3]);
	if (!vars[0] || !vars[1] || !vars[2] || !vars[3])
		return (ft_print_error(NULL, 2));
	cave->size = vars[0];
	ft_prepare_cave(cave, vars[1], vars[2], vars[3]);
	if (!cave->pids)
		return (ft_print_error(NULL, 3));
	if (args[4])
	{
		vars[4] = ft_atoi(args[4]);
		if (!vars[4])
			return (ft_print_error(cave, 2));
		cave->meal_count = vars[4];
	}
	return (0);
}

int main(int ac, char **av)
{
	t_cave	cave;

	if (ac != 5 && ac != 6)
		return(ft_print_error(NULL, 1));
	if (invalid_input(&cave, av + 1))
		return (1);
	return (0);
}
