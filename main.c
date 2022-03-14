/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-ass <svan-ass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 09:47:48 by svan-ass          #+#    #+#             */
/*   Updated: 2022/03/14 11:09:51 by svan-ass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutax(t_all *all)
{
	int	i;

	i = 0;
	all->forks = (pthread_mutex_t *)malloc(sizeof(*(all->forks)) \
	* all->nb_philosophers);
	if (!all->forks)
		errror("oh no mutex malloc");
	while (i < all->nb_philosophers)
	{
		if (pthread_mutex_init(&all->forks[i], NULL) != 0)
			errror("Mutex fork initialization failed");
		i++;
	}
	// if (pthread_mutex_init(&all->state, NULL) != 0)
	// 	errror("Mutex state initialization failed");
	if (pthread_mutex_init(&all->check_end, NULL) != 0)
		errror("Mutex check_end initialization failed");
	if (pthread_mutex_init(&all->meal_check, NULL) != 0)
		errror("Mutex meal_check initialization failed");
	return (0);
}

int	init_philosophers(t_all *all)
{
	int	i;

	i = 0;
	while (i < all->nb_philosophers)
	{
		all->philosopher[i].x = i + 1;
		all->philosopher[i].times_ate = 0;
		all->philosopher[i].last_meal = 0;
		all->philosopher[i].left_fork = i;
		all->philosopher[i].right_fork = (i + 1) % all->nb_philosophers;
		all->philosopher[i].all = all;
		i++;
	}
	return (0);
}

int	input(t_all *all, char **argv)
{
	all->nb_philosophers = ft_atoi(argv[1]);
	all->time_to_die = ft_atoi(argv[2]);
	all->time_to_eat = ft_atoi(argv[3]);
	all->time_to_sleep = ft_atoi(argv[4]);
	all->x_died = 0;
	all->all_ate = 0;
	if (all->nb_philosophers < 1 || all->time_to_die < 0 || \
	all->time_to_eat < 0 || all->time_to_sleep < 0)
		errror("invalid arguments");
	if (argv[5])
	{
		all->nb_times_must_eat = ft_atoi(argv[5]);
		if (all->nb_times_must_eat <= 0)
			return (1);
	}
	else
		all->nb_times_must_eat = -1;
	all->forks = NULL;
	all->philosopher = NULL;
	all->philosopher = (t_philosopher *)malloc(sizeof(*(all->philosopher)) \
	* all->nb_philosophers);
	if (!all->philosopher)
		errror("oh no philo malloc");
	init_philosophers(all);
	init_mutax(all);
	return (0);
}

int	check(int argc, char **argv)
{
	t_all	all;

	if (argc != 5 && argc != 6)
		errror("Invalid number of arguments");
	if (input(&all, argv) != 0)
		errror("there's an error somewhere:')");
	table(&all);
	// system("leaks philo");
	return (0);
}

int	main(int argc, char **argv)
{
	check(argc, argv);
	// system("leaks philo");
	return (0);
}
