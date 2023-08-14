/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azhadan <azhadan@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 21:15:26 by azhadan           #+#    #+#             */
/*   Updated: 2023/08/14 19:44:13 by azhadan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../h_files/philosopher.h"

void	philo_print(t_person *philo, char *str, int flag)
{
	unsigned long long	time;

	if (!philo->global->go)
		return ;
	pthread_mutex_lock(&philo->global->printf);
	time = current_time();
	printf("%05lld %lld %s\n", time - philo->global->start_time, philo->id, str);
	if (flag)
		pthread_mutex_unlock(&philo->global->printf);
}
