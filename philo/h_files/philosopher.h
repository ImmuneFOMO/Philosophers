/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azhadan <azhadan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 01:52:18 by azhadan           #+#    #+#             */
/*   Updated: 2023/08/06 22:39:18 by azhadan          ###   ########.fr       */
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
	pthread_mutex_t	*left_hand;
	pthread_mutex_t	*right_hand;
	int				person_do;
	//0 - nothing, die - 1, eat - 2, sleep - 3, think - 4, fed up - 5;
}					person_t;

typedef struct global
{
	long long		num_philo;
	long long		num_fed;
	int				go;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	long long		num_times_feed;
	person_t		*person;
}					global_t;

//philosopher.c
int					ft_check_args(char **argv, global_t *philos);
int					ft_isnums(char **str);
//helpers.c
long long			ft_atoi(const char *str);
void				current_time(long long *fill);

#endif