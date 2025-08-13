
#include "philosophers.h"
#include <stdio.h>

int	ft_handle_error(t_cave *cave, int error)
{
	ft_clean_cave(cave);
	printf("Error: ");
	if (error == 2)
		printf("%s\n", MAL_ERR);
	if (error == 3)
		printf("%s\n", MUT_ERR);
	if (error == 4)
		printf("%s\n", VAL_ERR);
	if (error == 5)
		printf("%s\n", FOR_ERR);
	return (error);
}
