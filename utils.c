/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-ass <svan-ass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 11:17:34 by svan-ass          #+#    #+#             */
/*   Updated: 2022/03/16 11:17:42 by svan-ass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	ft_atoi2(const char *str)
{
	int					i;
	unsigned long long	result;
	int					min;

	i = 0;
	min = 1;
	result = 0;
	while (*str != '\0' && ((*str >= 9 && *str <= 13) || *str == ' '))
		str++;
	if (*str != '\0' && *str == '-')
	{
		min = -1;
		str++;
	}
	else if (*str == '+')
		i++;
	while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9')
	{
		result = (result * 10) + (str[i++] - '0');
	}
	return (result * min);
}

int	check_min_max(const char *str)
{
	long long	temp;

	temp = ft_atoi2(str);
	if (temp >= INT_MIN && temp <= INT_MAX && ft_strlen(str) < 12)
		return (1);
	return (0);
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
			return (-1);
		if (check_min_max(str) == 0)
			return (-1);
	}
	return (result * min);
}
