/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-ass <svan-ass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 09:45:13 by svan-ass          #+#    #+#             */
/*   Updated: 2022/03/16 13:34:29 by svan-ass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdbool.h>
# include <limits.h>

typedef struct s_philosopher
{
	pthread_t			tid;
	int					x;
	int					times_ate;
	long				last_meal;
	int					left_fork;
	int					right_fork;
	struct s_all		*all;
}	t_philosopher;

typedef struct s_all
{
	int					nb_philosophers;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					nb_times_must_eat;
	int					x_died;
	pthread_mutex_t		state;
	pthread_mutex_t		status;
	pthread_mutex_t		meal_time;
	bool				end;
	int					all_ate;
	pthread_mutex_t		*forks;
	long				start_time;
	t_philosopher		*philosopher;
}	t_all;

/* main */
int		main(int argc, char **argv);
int		table(t_all *all);
void	monitoringg(t_all *all);

/* utils */
int		check(t_all *all);
void	action(t_all *all, int x, char *s);
long	timestamp(void);
void	ft_usleep(long time_to);

int		ft_atoi(const char *str);
size_t	ft_strlen(const char *str);

/* error */
int		errror(char *message);

#endif