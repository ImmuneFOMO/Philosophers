/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azhadan <azhadan@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 21:15:26 by azhadan           #+#    #+#             */
/*   Updated: 2023/08/25 19:36:44 by azhadan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../h_files/philosopher_bonus.h"

void	philo_print(t_person *philo, char *str, int flag)
{
	unsigned long long	time;

	(void)flag;
	sem_wait(philo->global->printf);
	time = current_time();
	printf("%05lld %ld %s\n", time - philo->global->start_time, philo->id, str);
	sem_post(philo->global->printf);
}

void	eating(t_person *philo)
{
	sem_wait(philo->global->forks);
	philo_print(philo, "has taken a fork", 1);
	sem_wait(philo->global->forks);
	philo_print(philo, "has taken a fork", 1);
	sem_wait(philo->global->checker);
	philo_print(philo, "is eating", 1);
	philo->time_last_food = current_time();
	sem_post(philo->global->checker);
}

int	hepler_start_philo(t_global *global)
{
	long long	i;

	global->start_time = current_time();
	i = 0;
	while (i < global->num_philo)
	{
		global->person[i]->id = i + 1;
		global->person[i]->global = global;
		global->person[i]->counter_fed = 0;
		global->person[i]->time_last_food = global->start_time;
		global->person[i]->pid = fork();
		if (global->person[i]->pid < 0)
			return (1);
		else if (global->person[i]->pid == 0)
			start_life(global->person[i]);
		i++;
	}
	return (0);
}

void	free_allocated_memory(t_global *global, int num)
{
	int	i;

	i = 0;
	while (i < num)
	{
		free(global->person[i]);
		++i;
	}
	free(global->person);
	sem_close(global->forks);
	sem_close(global->eating);
	sem_close(global->checker);
	sem_close(global->printf);
	sem_unlink("/printf");
	sem_unlink("/checker");
	sem_unlink("/eating");
	sem_unlink("/forks");
}
