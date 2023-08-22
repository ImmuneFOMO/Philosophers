/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azhadan <azhadan@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 09:29:26 by azhadan           #+#    #+#             */
/*   Updated: 2023/08/22 16:33:58 by azhadan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../h_files/philosopher_bonus.h"

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

long long	current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL))
		return (0);
	return ((time.tv_usec / 1000) + (time.tv_sec * (unsigned long)1000));
}

void	ft_free_philo(t_global *global)
{
	int	i;

	i = -1;
	printf("clean start\n");
	if (global->num_philo >= 1)
	{
		while (++i < global->num_philo)
			waitpid(-1, NULL, 0);
	}
	printf("clean end\n");
	i = -1;
	while (++i < global->num_philo)
		pthread_mutex_destroy(&global->forks[i]);
	if (global->locked)
		pthread_mutex_unlock(&global->printf);
	pthread_mutex_destroy(&global->checker);
	pthread_mutex_destroy(&global->printf);
	pthread_mutex_destroy(&global->eating);
	free(global->forks);
	free(global->person);
}

void	ft_custom_sleep(long long time, t_global *global)
{
	long long	st;

	(void)global;
	st = current_time();
	while ((current_time() - st) < time)
	{
		usleep(time / 10);
	}
}

void	ft_die_check(t_global *global)
{
	long long	i;

	while (get_go(global))
	{
		i = 0;
		pthread_mutex_lock(&global->checker);
		while (global->num_times_feed && i < global->num_philo
			&& global->person[i].counter_fed >= global->num_times_feed)
			i++;
		pthread_mutex_lock(&global->eating);
		if (i >= global->num_philo)
			global->go = 0;
		pthread_mutex_unlock(&global->eating);
		pthread_mutex_unlock(&global->checker);
		if (get_go(global) == 0)
			break ;
		helper_die_check(global);
	}
}
