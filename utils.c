/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-ass <svan-ass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 09:50:23 by svan-ass          #+#    #+#             */
/*   Updated: 2022/03/14 10:57:15 by svan-ass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (i < (n - 1) && s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
		i++;
	return ((unsigned char) s1[i] - (unsigned char) s2[i]);
}

long	timestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec) * 1000 + (tv.tv_usec) / 1000);
}

void	action(t_all *all, int x, char *s)
{
	int	i;

	i = x;
	pthread_mutex_lock(&all->state);
	if (all->x_died != 1 || all->all_ate != 1)
	{
		if (ft_strncmp(s, "died", 4) == 0)
		{
			printf("%li\t", timestamp() - all->start_time);
			printf("\033[0;31mPhilosopher %d %s\n\033[0m", x, s);
		}
		else
		{
			printf("%li\t", timestamp() - all->start_time);
			printf("Philosopher %d %s\n", x, s);
		}
	}
	pthread_mutex_unlock(&all->state);
}

void	ft_usleep(long time_to)
{
	long	present_time;

	present_time = timestamp();
	while (timestamp() < present_time + time_to)
		usleep(time_to);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	result;
	int	min;

	i = 0;
	min = 1;
	result = 0;
	if (*str != '\0' && *str == '-')
	{
		min = -1;
		str++;
	}
	while (str[i])
	{
		if (str[i] != '\0' && str[i] >= '0' && str[i] <= '9')
			result = (result * 10) + (str[i++] - '0');
		else
			errror("Not an digit");
		if (i > 10 && min == -1)
			return (1);
		if (i > 10)
			return (1);
	}
	return (result * min);
}
