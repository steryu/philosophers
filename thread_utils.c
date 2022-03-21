/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-ass <svan-ass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 09:50:23 by svan-ass          #+#    #+#             */
/*   Updated: 2022/03/16 11:38:49 by svan-ass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

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

void	ft_usleep(long time_to)
{
	long	present_time;

	present_time = timestamp();
	while (timestamp() < present_time + time_to)
		usleep(time_to);
}

long	timestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec) * 1000 + (tv.tv_usec) / 1000);
}

void	action(t_all *all, int x, char *s)
{
	pthread_mutex_lock(&all->state);
	if (ft_strncmp(s, "died", 4) == 0)
	{
		printf("%li\t", timestamp() - all->start_time);
		printf("\033[0;31mPhilosopher %d %s\n\033[0m", x + 1, s);
	}
	if (check(all) != 1)
	{
		printf("%li\t", timestamp() - all->start_time);
		printf("Philosopher %d %s\n", x + 1, s);
	}
	pthread_mutex_unlock(&all->state);
}
