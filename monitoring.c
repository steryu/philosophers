/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-ass <svan-ass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 11:19:27 by svan-ass          #+#    #+#             */
/*   Updated: 2022/03/16 13:15:44 by svan-ass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	change(t_all *all)
{
	pthread_mutex_lock(&all->status);
	all->end = true;
	pthread_mutex_unlock(&all->status);
}

int	check(t_all *all)
{
	int	status;

	pthread_mutex_lock(&all->status);
	if (all->end)
		status = 1;
	else
		status = 0;
	pthread_mutex_unlock(&all->status);
	return (status);
}

long	r_meal_time(t_philosopher *philo)
{
	long	time;

	pthread_mutex_lock(&philo->all->meal_time);
	time = philo->last_meal;
	pthread_mutex_unlock(&philo->all->meal_time);
	return (time);
}

void	monitoring(t_all *all)
{
	int		i;
	long	time_last_meal;

	i = 0;
	while (i < all->nb_philosophers)
	{
		time_last_meal = timestamp() - r_meal_time(&all->philosopher[i]);
		if ((time_last_meal > all->time_to_die))
		{
			change(all);
			if (all->philosopher[i].times_ate != 0)
				action(all, all->philosopher->x, "died");
			return ;
		}
		i++;
	}
}

void	monitoringg(t_all *all)
{
	while (!check(all))
		monitoring(all);
	free(all->philosopher);
	free(all->forks);
}
