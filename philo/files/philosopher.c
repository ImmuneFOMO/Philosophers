/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azhadan <azhadan@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 01:51:17 by azhadan           #+#    #+#             */
/*   Updated: 2023/08/08 01:37:44 by azhadan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../h_files/philosopher.h"

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
	global->num_times_feed = -1;
	if (argv[5])
		global->num_times_feed = ft_atoi(argv[5]);
	global->num_fed = 0;
	global->go = 1;
	return (0);
}

void *start_life(void *arg)
{
	t_global *tmp_global;
	int i;

	i = -1;
	tmp_global = (t_global *)arg;
	while (++i < tmp_global->num_philo)
	{
		printf("person[%d]_do:%d\n", i, tmp_global->person[i].person_do);
	}
	printf("test\n");
	return (NULL);
}

int	ft_start_philo(t_global *global)
{
	int i;

	pthread_mutex_init(&global->think, NULL);
	pthread_mutex_init(&global->eat, NULL);
	pthread_mutex_init(&global->dead, NULL);
	pthread_mutex_init(&global->printf, NULL);
	global->person = (t_person *)malloc(sizeof(t_person) * global->num_philo);
	if (!global->person)
		return (1);
	i = -1;
	current_time(&global->start_time);
	while (++i < global->num_philo)
	{
		global->person[i].person_do = nothing;
		global->person[i].left_hand = NULL;
		global->person[i].right_hand = NULL;
		global->person[i].id = i;
		if (pthread_create(&global->person[i].th, NULL, &start_life, global))
			return (0);
	}
	i = -1;
	while (++i < global->num_philo)
	{
		if (pthread_join(global->person[i].th, NULL))
			return (0);
	}
	
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
		free(global.person);
	}
	return (0);
}
