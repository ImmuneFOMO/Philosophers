/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azhadan <azhadan@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 21:15:26 by azhadan           #+#    #+#             */
/*   Updated: 2023/08/15 17:04:45 by azhadan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../h_files/philosopher.h"

void	philo_print(t_person *philo, char *str, int flag)
{
	unsigned long long	time;

	if (!get_global(philo->global))
		return ;
	pthread_mutex_lock(&philo->global->printf);
	time = current_time();
	printf("%05lld %lld %s\n", time - philo->global->start_time, philo->id, str);
	if (flag)
		pthread_mutex_unlock(&philo->global->printf);
	else
		philo->global->locked = 1;
}

int	get_global(t_global *global)
{
	int	i;

	i = 1;
	pthread_mutex_lock(&global->eating);
	if (global->go == 0)
		i = 0;
	pthread_mutex_unlock(&global->eating);
	return (i);
}
