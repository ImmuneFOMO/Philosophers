/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azhadan <azhadan@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 09:29:26 by azhadan           #+#    #+#             */
/*   Updated: 2023/08/09 23:22:05 by azhadan          ###   ########.fr       */
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

long long	current_time()
{
	struct timeval	time;

	if (gettimeofday(&time, NULL))
		return (0);
	return ((time.tv_usec / 1000) + (time.tv_sec * 1000));
}

void	ft_free_philo(t_global *global)
{
	int i;

	i = -1;
	if (global->num_philo > 1)
	{
		while (++i < global->num_philo)
			pthread_join(global->person->th, 0);
	}
	else
		pthread_detach(global->person[0].th);
	i = -1;
	while (++i < global->num_philo)
		pthread_mutex_destroy(&global->forks[i]);
	pthread_mutex_destroy(&global->printf);
	free(global->forks);
	free(global->person);
}

void	ft_custom_sleep(long long time, t_global *global)
{
	long long st;

	st = current_time();
	while (global->go)
	{
		if ((current_time() - st) >= time)
			break ;
	}
}

void	ft_die_check(t_global *global)
{
	long long time;
	long long i;
	
	while (global->go && global->num_fed < global->num_philo)
	{
		i = -1;
		while (global->go && global->num_times_feed && global->person[++i].counter_fed >= global->num_times_feed)
			global->num_fed = i;
		if (global->num_fed == global->num_philo)
			global->go = 0;
		i = -1;
		time = current_time();
		while (++i < global->num_philo && global->go)
		{
			if ((time - global->person[i].time_last_food) >= global->time_to_die)
			{
				global->go = 0;
				pthread_mutex_lock(&global->printf);
				printf("%lld %lld died\n", time - global->start_time, global->person[i].id);
			}
		}
	}
}
