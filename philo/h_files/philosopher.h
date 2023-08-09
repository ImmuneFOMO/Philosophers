/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azhadan <azhadan@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 01:52:18 by azhadan           #+#    #+#             */
/*   Updated: 2023/08/09 21:05:35 by azhadan          ###   ########.fr       */
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

typedef struct global t_global; 

typedef struct person
{
	long long		left_hand;
	long long		right_hand;
	long long		id;
	long long		time_last_food;
	long long		counter_fed;
	pthread_t		th;
	t_global		*global;
}					t_person;

typedef struct global
{
	long long		num_philo;
	long long		num_fed;
	int				go;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	long long		num_times_feed;
	long long		start_time;
	pthread_mutex_t printf;
	pthread_mutex_t	*forks;
	t_person		*person;
}					t_global;

//philosopher.c
int					ft_check_args(char **argv, t_global *philos);
int					ft_isnums(char **str);
void				*start_life(void *arg);
int					ft_start_philo(t_global *global);
//and main
//helpers.c
long long			ft_atoi(const char *str);
void				current_time(long long *fill);
void				ft_free_philo(t_global *global);
void				ft_custom_sleep(long long time, t_global *global);
void				ft_die_check(t_global *global);

#endif