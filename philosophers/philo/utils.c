
#include "philosophers.h"
#include <limits.h>
#include <stdio.h>
#include <sys/time.h>

static int	start(char *s)
{
	int	i;

	i = 0;
	while ((s[i] >= 9 && s[i] <= 13) || s[i] == ' ')
		i++;
	if (s[i] == '+')
		i++;
	s += i;
	while (*s)
	{
		if (*s < '0' || *s > '9')
			return (-1);
		s++;
	}
	return (i);
}

int	ft_atoi(char *s)
{
	int		i;
	long	val;

	i = start(s);
	if (i == -1)
		return (0);
	val = 0;
	while (s[i])
	{
		val = (val * 10) + (s[i] - '0');
		i++;
	}
	if (val < 0 || val > INT_MAX)
		return (0);
	return ((int)val);
}

long	ft_clock(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000L));
}

void	ft_printer(t_cave *c, t_philo *p, char *msg)
{
	long	now;

	pthread_mutex_lock(&c->print_lock);
	now = ft_clock() - c->start;
	printf("%ld %d %s\n", now, p->id, msg);
	pthread_mutex_unlock(&c->print_lock);
}
