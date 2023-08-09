/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snagulap <snagulap@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 18:52:08 by snagulap          #+#    #+#             */
/*   Updated: 2023/07/30 19:22:45 by snagulap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include<pthread.h>
# include<stdio.h>
# include<unistd.h>
# include<stdlib.h>
# include<sys/time.h>
# include <stdbool.h>

typedef struct s_philoso
{
	pthread_t		*thread;
	int				fork_r;
	int				fork_l;
	int				phi_num;
	int				eat_time;
	int				sleep_time;
	void			*philo_data;
	unsigned long	last_eat;
	unsigned long	ts;
	int				num_times_eaten;
}	t_philoso;

typedef struct s_philo
{
	unsigned int	num_philo;
	pthread_mutex_t	*chopsticks;
	pthread_mutex_t	print;
	unsigned long	time_to_die;
	unsigned long	time_to_eat;
	unsigned long	time_to_sleep;
	unsigned long	no_of_times_eaten;
	t_philoso		**phi;
	int				check;
}	t_philo;

int				ft_atoi(const char *str);
void			arrange(t_philo *philo);
void			phi_eat(t_philoso *ph);
void			phi_think(t_philoso *ph);
void			phi_sleep(t_philoso *ph);
unsigned long	time_(void);
void			t_wait(unsigned long time__, t_philo *philos);
int				phi_died(t_philoso *ph);
void			stop_(t_philoso *ph);
int				any_philosopher_died(t_philo *ph);
int				error_(void);
void			check__(char **argv);
#endif
