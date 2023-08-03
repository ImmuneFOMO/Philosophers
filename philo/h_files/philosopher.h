/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azhadan <azhadan@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 01:52:18 by azhadan           #+#    #+#             */
/*   Updated: 2023/08/03 23:50:35 by azhadan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct person
{
	pthread_mutex_t *left_hand;
	pthread_mutex_t *right_hand;
	int		person_do;
	//0 - nothing, die - 1, eat - 2, sleep - 3, think - 4, fed up - 5;
}	person_t

typedef struct global
{
	long long		num_philo;
	long long		num_fed;
	int				go;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
    long long		num_times_feed;
	person_t		philo;
}					global_t;

//philosopher.c
void				ft_check_args(char **argv, hands_t **philos);
int					ft_isnums(char **str);
//helpers.c
long long			ft_atoi(const char *str);
void				current_time(long long *fill);

#endif