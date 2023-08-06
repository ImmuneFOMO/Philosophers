/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azhadan <azhadan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 01:51:17 by azhadan           #+#    #+#             */
/*   Updated: 2023/08/06 23:22:05 by azhadan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../h_files/philosopher.h"

// void	*test(void *argv)
// {
// 	int		i;
// 	hands_t	*hands;

// 	hands = (hands_t *)argv;
// 	i = 0;
// 	while (i < 10000)
// 	{
// 		pthread_mutex_lock(&hands->left_h);
// 		(hands->test)++;
// 		pthread_mutex_unlock(&hands->left_h);
// 		i++;
// 	}
// 	return (NULL);
// }

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

int	ft_check_args(char **argv, global_t *philos)
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
	philos->num_philo = ft_atoi(argv[1]);
	philos->time_to_die = ft_atoi(argv[2]);
	philos->time_to_eat = ft_atoi(argv[3]);
	philos->time_to_sleep = ft_atoi(argv[4]);
	philos->num_times_feed = -1;
	if (argv[5])
		philos->num_times_feed = ft_atoi(argv[5]);
	philos->num_fed = 0;
	philos->go = 1;
	return (0);
}

int	main(int argc, char **argv)
{
	global_t	global;

	if (argc >= 5 && argc <= 6)
	{
		if (ft_check_args(argv, &global))
			return (-1);
	}
	return (0);
}
