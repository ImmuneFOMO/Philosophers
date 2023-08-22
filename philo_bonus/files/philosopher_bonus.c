/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azhadan <azhadan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 01:51:17 by azhadan           #+#    #+#             */
/*   Updated: 2023/08/22 20:06:39 by azhadan          ###   ########.fr       */
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

int	ft_check_args(char **argv, t_global *global)
{
	int	i;

	i = 0;
	if (ft_isnums(argv))
		return (1);
	while (argv[++i])
	{
		if (ft_atoi(argv[i]) <= 0)
			return (1);
	}
	global->num_philo = ft_atoi(argv[1]);
	global->time_to_die = ft_atoi(argv[2]);
	global->time_to_eat = ft_atoi(argv[3]);
	global->time_to_sleep = ft_atoi(argv[4]);
	global->num_times_feed = 0;
	if (argv[5])
		global->num_times_feed = ft_atoi(argv[5]);
	global->num_fed = 0;
	global->go = 1;
	return (0);
}

void	*start_life(void *arg)
{
	t_person	*philo;

	philo = (t_person *)arg;
	if (philo->global->num_philo == 1)
	{
		philo_print(philo, "has taken a fork", 1);
		return (NULL);
	}
	if (philo->global->num_philo > 1 && philo->id % 2)
		ft_custom_sleep(40, philo->global);
	while (get_go(philo->global))
	{
		eating(philo);
		ft_custom_sleep(philo->global->time_to_eat, philo->global);
		pthread_mutex_lock(&philo->global->checker);
		philo->counter_fed++;
		pthread_mutex_unlock(&philo->global->checker);
		pthread_mutex_unlock(&philo->global->forks[philo->left_hand]);
		pthread_mutex_unlock(&philo->global->forks[philo->right_hand]);
		philo_print(philo, "is sleeping", 1);
		ft_custom_sleep(philo->global->time_to_sleep, philo->global);
		philo_print(philo, "is thinking", 1);
	}
	return (NULL);
}

int	ft_start_philo(t_global *global)
{
	long long	i;

	global->person = (t_person *)malloc(sizeof(t_person) * global->num_philo);
	if (!global->person)
		return (1);
	global->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* global->num_philo);
	if (!global->forks)
	{
		free(global->person);
		return (1);
	}
	i = -1;
	while (++i < global->num_philo)
	{
		if (pthread_mutex_init(&global->forks[i], NULL))
		{
			free(global->person);
			free(global->forks);
			return (1);
		}
	}
	if (hepler_start_philo(global))
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_global	global;

	if (argc >= 5 && argc <= 6)
	{
		if (ft_check_args(argv, &global))
			return (-1);
		if (ft_start_philo(&global))
			return (-1);
		ft_die_check(&global);
		ft_free_philo(&global);
	}
	return (0);
}
