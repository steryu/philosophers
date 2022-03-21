/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-ass <svan-ass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 11:18:44 by svan-ass          #+#    #+#             */
/*   Updated: 2022/03/16 13:37:52 by svan-ass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	exit_table(t_all *all)
{
	int	i;

	i = 0;
	while (i < all->nb_philosophers)
	{
		if (pthread_join(all->philosopher[i].tid, NULL) != 0)
			return (1);
		i++;
	}
	return (1);
}

void	eating(t_philosopher *philosopher)
{
	t_all	*all;

	all = philosopher->all;
	if (philosopher->x == 0)
		all->philosopher->right_fork = all->nb_philosophers - 1;
	pthread_mutex_lock(&all->forks[philosopher->left_fork]);
	action(all, philosopher->x, "has taken a fork");
	pthread_mutex_lock(&all->forks[philosopher->right_fork]);
	action(all, philosopher->x, "has taken a fork");
	pthread_mutex_lock(&all->meal_time);
	philosopher->last_meal = timestamp();
	pthread_mutex_unlock(&all->meal_time);
	action(all, philosopher->x, "is eating");
	ft_usleep(all->time_to_eat);
	philosopher->times_ate--;
	pthread_mutex_unlock(&all->forks[philosopher->left_fork]);
	pthread_mutex_unlock(&all->forks[philosopher->right_fork]);
}

void	*philosopher(void *num)
{
	t_philosopher	*philo;
	t_all			*all;

	philo = (t_philosopher *)num;
	all = philo->all;
	if (philo->x % 2)
		ft_usleep(all->time_to_eat - 1);
	while ((check(all) != 1) && philo->times_ate != 0)
	{
		eating(philo);
		action(all, philo->x, "is sleeping");
		ft_usleep(all->time_to_sleep);
		action(all, philo->x, "is thinking");
	}
	return (NULL);
}

int	table(t_all *all)
{
	int				i;
	t_philosopher	*philo;

	i = 0;
	philo = all->philosopher;
	all->start_time = timestamp();
	while (i < all->nb_philosophers)
	{
		philo[i].last_meal = timestamp();
		pthread_create(&philo[i].tid, NULL, philosopher, &philo[i]);
		i++;
	}
	monitoringg(all);
	exit_table(all);
	return (0);
}
