
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <sys/time.h>
#include "philo_bonus.h"

long	ft_clock(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000L));
}

void	ft_printer(int i, int a, char *m, t_cave *c)
{
	long	now;

	now = ft_clock() - c->start;
	sem_wait(c->printer);
	printf("\033[%dm%ld %d %s\033[0m\n", a, now, i, m);
	sem_post(c->printer);
}

int	ft_atopi(char *s)
{
	long	result;

	result = 0;
	while ((*s >= 9 && *s <= 13) || *s == ' ')
		s++;
	if (*s == '+')
		s++;
	while (*s >= '0' && *s <= '9')
	{
		result *= 10;
		result += *s - '0';
		s++;
	}
	while ((*s >= 9 && *s <= 13) || *s == ' ')
		s++;
	if (*s || result < 0 || result > INT_MAX)
		return (0);
	return ((int)result);
}
