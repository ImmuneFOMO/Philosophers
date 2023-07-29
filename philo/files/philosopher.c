/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azhadan <azhadan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 01:51:17 by azhadan           #+#    #+#             */
/*   Updated: 2023/07/29 18:15:36 by azhadan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../h_files/philosopher.h"

void	*test(void *argv)
{
	int		i;
	hands_t	*hands;

	hands = (hands_t *)argv;
	i = 0;
	while (i < 10000)
	{
		pthread_mutex_lock(&hands->left_h);
		(hands->test)++;
		pthread_mutex_unlock(&hands->left_h);
		i++;
	}
	return (NULL);
}

void	start_hands(hands_t **hands)
{
	(*hands)->test = 0;
	pthread_mutex_init(&(*hands)->left_h, NULL);
	pthread_mutex_init(&(*hands)->right_h, NULL);
}

int	main(int argc, char **argv)
{
	pthread_t	t_one;
	pthread_t	t_two;
	hands_t		*hands;

	(void)argc;
	(void)argv;
	if (argc == 3)
	{
		hands = (hands_t *)malloc(sizeof(hands_t));
		if (!hands)
			exit(1);
		start_hands(&hands);
		pthread_create(&t_one, NULL, test, hands);
		pthread_create(&t_two, NULL, test, hands);
		pthread_join(t_one, NULL);
		pthread_join(t_two, NULL);
		printf("result:%d\n", hands->test);
		pthread_mutex_destroy(&hands->left_h);
		pthread_mutex_destroy(&hands->right_h);
		free(hands);
	}
	return (0);
}
