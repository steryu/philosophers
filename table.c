/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-ass <svan-ass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 11:18:44 by svan-ass          #+#    #+#             */
/*   Updated: 2022/03/14 11:09:56 by svan-ass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	exit_table(t_all *all, t_philosopher *philo)
{
	int	i;

	i = 0;
	while (i < all->nb_philosophers)
	{
		pthread_join(philo[i].tid, NULL);
		i++;
	}	
	i = 0;
	while (i < all->nb_philosophers)
	{
		pthread_mutex_destroy(&all->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&all->state);
	pthread_mutex_destroy(&all->check_end);
	free(all->philosopher);
	free(all->forks);
}

void	ate_enough(t_all *all)
{
	pthread_mutex_lock(&all->state);
	printf("%li\t", timestamp() - all->start_time);
	printf("\033[0;32mevery philosopher ate %d times\n\033[0m", all->nb_times_must_eat);
	pthread_mutex_unlock(&all->state);
}

void	*checker(t_all *all, t_philosopher *philo)
{
	int	i;

	i = 0;
	while (all->x_died != 1)
	{
		while (i < all->nb_philosophers && all->x_died != 1)
		{
			pthread_mutex_lock(&all->meal_check);
			if ((timestamp() - all->philosopher->last_meal) > all->time_to_die)
			{
				action(all, all->philosopher->x, "died");
				all->x_died = 1;
				pthread_mutex_unlock(&all->check_end);
				return (NULL);
			}
			pthread_mutex_unlock(&all->meal_check);
			i++;
		}
		i = 0;
		if (all->nb_times_must_eat > -1)
		{
			while (philo[i].x && philo[i].times_ate == all->nb_times_must_eat)
				i++;
			if (i == all->nb_philosophers)
			{
				ate_enough(all);
				all->all_ate = 1;
				pthread_mutex_unlock(&all->check_end);
				return (NULL);
			}
		}
	}
	return (NULL);
}

void	eating(t_philosopher *philosopher)
{
	t_all	*all;

	all = philosopher->all;
	pthread_mutex_lock(&all->forks[philosopher->left_fork]);
	action(all, philosopher->x, "has taken a fork");
	pthread_mutex_lock(&all->forks[philosopher->right_fork]);
	action(all, philosopher->x, "has taken a fork");
	pthread_mutex_lock(&all->meal_check);
	action(all, philosopher->x, "is eating");
	philosopher->last_meal = timestamp();
	pthread_mutex_unlock(&all->meal_check);
	ft_usleep(all->time_to_eat);
	(philosopher->times_ate)++;
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
		ft_usleep(all->time_to_eat);
	while (all->x_died != 1 && all->all_ate != 1)
	{
		eating(philo);
		if (all->x_died == 1 || all->all_ate == 1)
			break ;
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
	pthread_mutex_init(&all->state, NULL);
	pthread_mutex_lock(&all->check_end);
	while (i < all->nb_philosophers)
	{
		philo[i].last_meal = timestamp();
		pthread_create(&philo[i].tid, NULL, philosopher, &philo[i]);
		i++;
	}
	checker(all, all->philosopher);
	exit_table(all, philo);
	return (0);
}
