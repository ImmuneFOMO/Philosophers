/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azhadan <azhadan@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 09:29:26 by azhadan           #+#    #+#             */
/*   Updated: 2023/08/08 21:26:37 by azhadan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../h_files/philosopher.h"

long long	ft_atoi(const char *str)
{
	long long	num;
	int			s;

	s = 1;
	num = 0;
	while ((*str >= '\t' && *str <= '\r') || (*str == ' '))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			s *= -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		num = num * 10 + (*str - '0');
		str++;
	}
	return (num * s);
}

void	current_time(long long *fill)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL))
		return ;
	*fill = (time.tv_usec / 1000) + (time.tv_sec * 1000);
}

void	ft_free_philo(t_global *global)
{
	free(global->forks);
	free(global->person);
}
