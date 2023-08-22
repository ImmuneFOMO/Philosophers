/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azhadan <azhadan@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 21:15:26 by azhadan           #+#    #+#             */
/*   Updated: 2023/08/22 17:40:33 by azhadan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../h_files/philosopher_bonus.h"

void	philo_print(t_person *philo, char *str, int flag)
{
	unsigned long long	time;

	if (!get_go(philo->global))
		return ;
	pthread_mutex_lock(&philo->global->printf);
	time = current_time();
	printf("%05lld %lld %s\n", time - philo->global->start_time, philo->id, str);
	if (flag)
		pthread_mutex_unlock(&philo->global->printf);
	else
		philo->global->locked = 1;
}

int	get_go(t_global *global)
{
	int	i;

	i = 1;
	pthread_mutex_lock(&global->eating);
	if (global->go == 0)
		i = 0;
	pthread_mutex_unlock(&global->eating);
	return (i);
}

void	eating(t_person *philo)
{
	pthread_mutex_lock(&philo->global->forks[philo->right_hand]);
	philo_print(philo, "has taken a fork", 1);
	pthread_mutex_lock(&philo->global->forks[philo->left_hand]);
	philo_print(philo, "has taken a fork", 1);
	pthread_mutex_lock(&philo->global->checker);
	philo_print(philo, "is eating", 1);
	philo->time_last_food = current_time();
	pthread_mutex_unlock(&philo->global->checker);
}

void	helper_die_check(t_global *global)
{
	long long	i;
	long long	time;

	i = 0;
	while (i < global->num_philo && get_go(global))
	{
		pthread_mutex_lock(&global->checker);
		time = current_time();
		if ((time \
		- global->person[i].time_last_food) >= global->time_to_die)
		{
			philo_print(&global->person[i], "died", 0);
			pthread_mutex_lock(&global->eating);
			global->go = 0;
			pthread_mutex_unlock(&global->eating);
		}
		i++;
		pthread_mutex_unlock(&global->checker);
	}
}

int	hepler_start_philo(t_global *global)
{
	long long	i;
	pid_t		pid;

	pthread_mutex_init(&global->printf, NULL);
	pthread_mutex_init(&global->checker, NULL);
	pthread_mutex_init(&global->eating, NULL);
	global->start_time = current_time();
	global->locked = 0;
	i = 0;
	while (i < global->num_philo)
	{
		global->person[i].left_hand = i;
		global->person[i].right_hand = (i + 1) % global->num_philo;
		global->person[i].id = i + 1;
		global->person[i].global = global;
		global->person[i].counter_fed = 0;
		global->person[i].time_last_food = current_time();
		global->pids[i] = fork();
		if (global->pids[i] < 0)
		{
			while (--i >= 0)
				kill(global->pids[i], SIGKILL);
			return (1);
		}
		else if (global->pids[i] == 0)
		{
			start_life(global);
			exit(0);
		}
		i++;
	}
	return (0);
}
