/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_bonus.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azhadan <azhadan@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 01:52:18 by azhadan           #+#    #+#             */
/*   Updated: 2023/08/27 16:59:13 by azhadan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_BONUS_H
# define PHILOSOPHER_BONUS_H
# include <fcntl.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct global	t_global;

typedef struct person
{
	time_t				id;
	time_t				time_last_food;
	time_t				counter_fed;
	pid_t				pid;
	pthread_t			checker;
	t_global			*global;
}						t_person;

typedef struct global
{
	time_t				num_philo;
	time_t				time_to_die;
	time_t				time_to_eat;
	time_t				time_to_sleep;
	time_t				num_times_feed;
	time_t				start_time;
	t_person			**person;
	sem_t				*printf;
	sem_t				*checker;
	sem_t				*eating;
	sem_t				*forks;
	sem_t				*stop;
}						t_global;

// philosopher_bonus.c
int						ft_check_args(char **argv, t_global *global, \
t_person *philos);
int						ft_isnums(char **str);
int						start_life(t_person *philo);
int						ft_start_philo(t_global *global, t_person *philos);
// and main
// helpers_bonus.c
long long				ft_atoi(const char *str);
time_t					current_time(void);
void					ft_free_philo(t_global *global, t_person *philo);
void					ft_custom_sleep(long long time, t_global *global);
void					*ft_die_check(void *person);
// output_bonus.c
void					philo_print(t_person *philo, char *str, int flag);
int						eating(t_person *philo);
int						hepler_start_philo(t_global *global, t_person *philos);
void					free_allocated_memory(t_global *global, \
t_person *philos);
void					ft_die(t_person *philo, t_global *global, int flag);

#endif