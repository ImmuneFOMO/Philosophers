/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azhadan <azhadan@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 21:15:26 by azhadan           #+#    #+#             */
/*   Updated: 2023/08/23 00:46:12 by azhadan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../h_files/philosopher_bonus.h"

void	philo_print(t_person *philo, char *str, int flag)
{
	unsigned long long	time;

	if (!get_go(philo->global))
		return ;
	sem_wait(&philo->global->printf);
	time = current_time();
	printf("%05lld %lld %s\n", time - philo->global->start_time, philo->id,
			str);
	if (flag)
		sem_post(&philo->global->printf);
	else
		philo->global->locked = 1;
}

int	get_go(t_global *global)
{
	int	i;

	sem_wait(&global->eating);
	if (global->go == 0)
		i = 0;
	else
		i = 1;
	sem_post(&global->eating);
	return (i);
}

void	eating(t_person *philo)
{
	sem_wait(&philo->global->forks);
	philo_print(philo, "has taken a fork", 1);
	sem_wait(&philo->global->forks);
	philo_print(philo, "has taken a fork", 1);
	sem_wait(&philo->global->checker);
	philo_print(philo, "is eating", 1);
	philo->time_last_food = current_time();
	sem_post(&philo->global->checker);
}

void	helper_die_check(t_global *global)
{
	long long	i;
	long long	time;

	i = 0;
	while (i < global->num_philo && get_go(global))
	{
		sem_wait(&global->checker);
		time = current_time();
		if ((time - global->person[i].time_last_food) >= global->time_to_die)
		{
			philo_print(&global->person[i], "died", 0);
			sem_wait(&global->eating);
			global->go = 0;
			sem_post(&global->eating);
		}
		i++;
		sem_post(&global->checker);
	}
}

int	hepler_start_philo(t_global *global)
{
	long long	i;
	pid_t		pid;

	if (sem_init(&global->checker, 0, 1))
		return (1);
	if (sem_init(&global->eating, 0, 1))
		return (1);
	if (sem_init(&global->printf, 0, 1))
		return (1);
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
		pid = fork();
		if (pid < 0)
			return (1);
		else if (pid == 0)
		{
			start_life(&global->person[i]);
			exit(0);
		}
		else
			global->person[i].pid = pid;
		i++;
	}
	return (0);
}
