/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-ass <svan-ass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 09:47:48 by svan-ass          #+#    #+#             */
/*   Updated: 2022/03/16 13:47:44 by svan-ass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	errror(char *message)
{
	if (message)
	{
		write(2, message, ft_strlen(message));
		write(2, "\n", 1);
		return (1);
	}
	return (1);
}

int	init_mutax(t_all *all)
{
	int	i;

	i = 0;
	all->forks = NULL;
	all->forks = (pthread_mutex_t *)malloc(sizeof(*(all->forks)) \
	* all->nb_philosophers);
	if (!all->forks)
		return (errror("oh no mutex malloc"));
	while (i < all->nb_philosophers)
	{
		if (pthread_mutex_init(&all->forks[i], NULL) != 0)
			return (1);
		i++;
	}
	if (pthread_mutex_init(&all->state, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&all->status, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&all->meal_time, NULL) != 0)
		return (1);
	return (0);
}

int	init_philosophers(t_all *all)
{
	int	i;

	i = 0;
	all->philosopher = NULL;
	all->philosopher = (t_philosopher *)malloc(sizeof(*(all->philosopher)) \
	* all->nb_philosophers);
	if (!all->philosopher)
		return (errror("oh no philo malloc"));
	while (i < all->nb_philosophers)
	{
		all->philosopher[i].x = i;
		all->philosopher[i].times_ate = all->nb_times_must_eat;
		all->philosopher[i].last_meal = 0;
		all->philosopher[i].left_fork = i;
		all->philosopher[i].right_fork = all->philosopher->x - 1;
		all->philosopher[i].all = all;
		i++;
	}
	return (0);
}

int	input(t_all *all, char **argv)
{
	all->x_died = 0;
	all->all_ate = 0;
	all->end = false;
	all->nb_philosophers = ft_atoi(argv[1]);
	all->time_to_die = ft_atoi(argv[2]);
	all->time_to_eat = ft_atoi(argv[3]);
	all->time_to_sleep = ft_atoi(argv[4]);
	if (all->nb_philosophers < 1 || all->time_to_die < 0 || \
	all->time_to_eat < 0 || all->time_to_sleep < 0)
		return (errror("invalid arguments"));
	if (argv[5])
	{
		all->nb_times_must_eat = ft_atoi(argv[5]);
		if (all->nb_times_must_eat <= 0)
			return (errror("invalid arguments"));
	}
	else
		all->nb_times_must_eat = -1;
	init_philosophers(all);
	if (init_mutax(all) != 0)
		return (errror("failed to intialize mutex"));
	return (0);
}

int	main(int argc, char **argv)
{
	t_all	all;

	if (argc != 5 && argc != 6)
		return (errror("invalid number of arguments"));
	if (input(&all, argv) != 0)
		return (1);
	if (table(&all))
		return (errror("Error creating the threads"));
	return (0);
}
