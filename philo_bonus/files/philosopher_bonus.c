/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azhadan <azhadan@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 01:51:17 by azhadan           #+#    #+#             */
/*   Updated: 2023/08/27 18:06:01 by azhadan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../h_files/philosopher_bonus.h"

int	ft_isnums(char **str)
{
	int	i;
	int	j;

	i = 1;
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			if (str[i][j] > '9' || str[i][j] < '0')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	ft_check_args(char **argv, t_global *global, t_person *philos)
{
	global->num_philo = ft_atoi(argv[1]);
	global->time_to_die = ft_atoi(argv[2]);
	global->time_to_eat = ft_atoi(argv[3]);
	global->time_to_sleep = ft_atoi(argv[4]);
	global->num_times_feed = 0;
	if (argv[5])
		global->num_times_feed = ft_atoi(argv[5]);
	sem_unlink("/printf");
	sem_unlink("/checker");
	sem_unlink("/eating");
	sem_unlink("/forks");
	sem_unlink("/stop");
	global->printf = sem_open("/printf", O_CREAT, 0664, 1);
	global->checker = sem_open("/checker", O_CREAT, 0644, 1);
	global->eating = sem_open("/eating", O_CREAT, 0644, 1);
	global->forks = sem_open("/forks", O_CREAT, 0644, global->num_philo);
	global->stop = sem_open("/stop", O_CREAT, 0644, 1);
	if (global->forks == SEM_FAILED || global->eating == SEM_FAILED
		|| global->checker == SEM_FAILED || global->printf == SEM_FAILED || \
		global->stop == SEM_FAILED)
	{
		free_allocated_memory(global, philos);
		return (1);
	}
	return (0);
}

int	start_life(t_person *philo)
{
	philo->time_last_food = current_time();
	if (pthread_create(&philo->checker, NULL, &ft_die_check, philo))
		exit(1);
	if (pthread_detach(philo->checker))
		exit(1);
	if (philo->id % 2)
		ft_custom_sleep(30, philo->global);
	while (1)
	{
		if (philo->id % 2)
			usleep(100);
		if (eating(philo))
		{
			sem_post(philo->global->stop);
			while (1)
			{
				sem_wait(philo->global->checker);
				philo->time_last_food = current_time();
				sem_post(philo->global->checker);
			}
			return (1);
		}
	}
	return (0);
}

int	ft_start_philo(t_global *global, t_person *philos)
{
	if (hepler_start_philo(global, philos))
	{
		free_allocated_memory(global, philos);
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_global	*global;
	t_person	*persons;
	int			i;

	global = NULL;
	persons = NULL;
	i = 0;
	if (argc >= 5 && argc <= 6)
	{
		if (ft_isnums(argv))
			return (1);
		while (argv[++i])
		{
			if (ft_atoi(argv[i]) <= 0)
				return (1);
		}
		global = (t_global *)malloc(sizeof(t_global));
		persons = (t_person *)malloc(sizeof(t_person) * ft_atoi(argv[1]) + 1);
		if (ft_check_args(argv, global, persons))
			return (-1);
		sem_wait(global->stop);
		if (ft_start_philo(global, persons))
			return (-1);
	}
	return (0);
}
