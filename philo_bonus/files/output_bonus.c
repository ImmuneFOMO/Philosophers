/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azhadan <azhadan@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 21:15:26 by azhadan           #+#    #+#             */
/*   Updated: 2023/08/23 18:34:34 by azhadan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../h_files/philosopher_bonus.h"

void	philo_print(t_person *philo, char *str, int flag)
{
	unsigned long long	time;

	(void)flag;
	sem_wait(&philo->global->printf);
	time = current_time();
	printf("%05lld %ld %s\n", time - philo->global->start_time, philo->id, str);
	sem_post(&philo->global->printf);
}

void	eating(t_person *philo)
{
	sem_wait(&philo->global->forks);
	philo_print(philo, "has taken a fork", 1);
	sem_wait(&philo->global->forks);
	philo_print(philo, "has taken a fork", 1);
	sem_wait(&philo->global->checker);
	philo_print(philo, "is eating", 1);
	printf("time:%ld time_last_food:%ld\n",current_time(), philo->time_last_food);
	philo->time_last_food = current_time();
	sem_post(&philo->global->checker);
}

int	hepler_start_philo(t_global *global)
{
	long long	i;

	if (sem_init(&global->checker, 0, 1))
		return (1);
	if (sem_init(&global->eating, 0, 1))
		return (1);
	if (sem_init(&global->printf, 0, 1))
		return (1);
	printf("instilize time before:%ld\n", current_time());
	global->start_time = current_time();
	printf("instilize time before value:%ld\n", global->start_time);
	global->locked = 0;
	i = 0;
	while (i < global->num_philo)
	{
		global->person[i].id = i + 1;
		global->person[i].global = global;
		global->person[i].counter_fed = 0;
		printf("instilize time:%ld\n", current_time());
		global->person[i].time_last_food = current_time();
		printf("instilize time_last_food:%ld\n", global->person[i].time_last_food);
		global->person[i].pid = fork();
		if (global->person[i].pid < 0)
			return (1);
		else if (global->person[i].pid == 0)
			start_life(&global->person[i]);
		i++;
	}
	return (0);
}
