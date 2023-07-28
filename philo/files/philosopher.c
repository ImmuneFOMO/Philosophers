/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azhadan <azhadan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 01:51:17 by azhadan           #+#    #+#             */
/*   Updated: 2023/07/28 05:19:28 by azhadan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../h_files/philosopher.h"

void	*test(void *argv)
{
	int	i;

	i = 0;
	while (i != 20)
	{
		printf("%s\n", (char *)argv);
		i++;
		usleep(6000);
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	pthread_t	t_one;
	pthread_t	t_two;

	(void)argc;
	(void)argv;
	if (argc == 3)
	{
		pthread_create(&t_one, NULL, test, argv[1]);
		pthread_create(&t_two, NULL, test, argv[2]);
		usleep(30000);
	}
	return (0);
}
