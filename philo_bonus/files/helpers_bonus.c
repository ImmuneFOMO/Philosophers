/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azhadan <azhadan@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 09:29:26 by azhadan           #+#    #+#             */
/*   Updated: 2023/08/27 01:50:51 by azhadan          ###   ########.fr       */
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

time_t	current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL))
		return (0);
	return ((time.tv_usec / 1000) + (time.tv_sec * 1000));
}

void	ft_free_philo(t_global *global)
{
	long long	i;
	int			value;

	i = -1;
	while (++i < global->num_philo)
	{
		waitpid(-1, &value, 0);
		if (value != 0)
		{
			i = -1;
			while (++i < global->num_philo)
				kill(global->person[i]->pid, SIGTERM);
			break ;
		}
	}
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

void	*ft_die_check(void *person)
{
	t_person	*philo;
	time_t		time;

	philo = (t_person *)person;
	while (1)
	{
		sem_wait(philo->global->checker);
		time = current_time();
		if ((time - philo->time_last_food) >= philo->global->time_to_die)
		{
			sem_post(philo->global->checker);
			philo_print(philo, "died", 0);
			philo->global->life = 0;
			return (NULL);
		}
		if (philo->counter_fed >= philo->global->num_times_feed && \
		philo->global->num_times_feed > 0)
		{
			sem_post(philo->global->checker);
			break ;
		}
		sem_post(philo->global->checker);
	}
	return (NULL);
}
