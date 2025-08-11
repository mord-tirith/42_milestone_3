/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minilib.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thenriqu <thenriqu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 14:40:23 by thenriqu          #+#    #+#             */
/*   Updated: 2025/08/11 14:43:37 by thenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>

static int	check_valid(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] < 9 || s[i] > 13)
		{
			if (s[i] != ' ' && (s[i] < '0' || s[i] > '9') && s[i] != '+')
				return (0);
			if (s[i] == '+' && (s[i + 1] < '0' || s[i + 1] > '9'))
				return (0);
		}
		i++;
	}
	return (1);
}

int	ft_atoi(char *s)
{
	long	res;

	res = 0;
	if (!check_valid(s))
		return (0);
	while ((*s >= 9 && *s <= 13) || *s == ' ')
		s++;
	if (*s == '+')
		s++;
	while (*s >= '0' && *s <= '9')
	{
		res = (res * 10) + (*s - '0');
		s++;
	}
	if (res > INT_MAX || res < 0)
		return (0);
	return ((int)res);
}
