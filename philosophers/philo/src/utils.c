
#include "philo.h"
#include <stdio.h>
#include <limits.h>
#include <pthread.h>
#include <sys/time.h>

long	ft_clock(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000L));
}

void	ft_printer(int action, char *msg, t_philo *philo)
{
	long	now;

	pthread_mutex_lock(&philo->table->print_lock);
	printf("\033[%dm", action);
	now = ft_clock() - philo->table->start;
	printf("%ld %d %s\n\033[0m", now, philo->id, msg);
	pthread_mutex_unlock(&philo->table->print_lock);
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
	if (*s || result < 0 || result > INT_MAX)
		return (0);
	return ((int)result);
}
