/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azhadan <azhadan@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 01:51:17 by azhadan           #+#    #+#             */
/*   Updated: 2023/08/03 23:50:49 by azhadan          ###   ########.fr       */
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

void	start_hands(hands_t **hands)
{
	(*hands)->test = 0;
	pthread_mutex_init(&(*hands)->left_h, NULL);
	pthread_mutex_init(&(*hands)->right_h, NULL);
}

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

void	ft_check_args(char **argv, hands_t **philos)
{
	int	i;

	i = 0;
	if (ft_isnums(argv))
		exit(1);
	while (argv[++i])
	{
		if (ft_atoi(argv[i]) <= 0)
			exit(1);
	}
	*philos = (hands_t *)malloc(sizeof(hands_t));
	(*philos)->num_philo = ft_atoi(argv[1]);
	(*philos)->time_to_die = ft_atoi(argv[2]);
	(*philos)->time_to_eat = ft_atoi(argv[3]);
	(*philos)->time_to_sleep = ft_atoi(argv[4]);
	(*philos)->num_times_feed = -1;
	if (argv[5])
		(*philos)->num_times_feed = ft_atoi(argv[5]);
	(*philos)->num_fed = 0;
	(*philos)->go = 1;
	
}

int	main(int argc, char **argv)
{
	long long	time;
	long long	time_2;
	global_t		*global;

	(void)argv;
	if (argc >= 5 && argc <= 6)
	{
		current_time(&time);
		ft_check_args(argv, &hands);
		if (!hands)
			exit(1);
		start_hands(&hands);
		usleep(10000);
		current_time(&time_2);
		printf("past:%lld\n", time_2 - time);
		free(hands);
	}
	return (0);
}
