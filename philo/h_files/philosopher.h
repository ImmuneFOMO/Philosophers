/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azhadan <azhadan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 01:52:18 by azhadan           #+#    #+#             */
/*   Updated: 2023/07/31 15:53:05 by azhadan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H
# include <pthread.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct hands
{
	int				num_philo;
	pthread_mutex_t	left_h;
	pthread_mutex_t	right_h;
	int				test;
}					hands_t;

//philosopher.c
void				ft_check_args(char **argv, hands_t **philos);
int					ft_isnums(char **str);
//helpers.c
long long			ft_atoi(const char *str);
void				current_time(uint64_t *fill);

#endif