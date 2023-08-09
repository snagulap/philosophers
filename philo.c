/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snagulap <snagulap@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 20:09:07 by snagulap          #+#    #+#             */
/*   Updated: 2023/07/29 19:28:10 by snagulap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

void	arrange(t_philo *philos)
{
	unsigned int	i;

	i = 0;
	while (i < philos->num_philo)
	{
		philos->phi[i]->fork_r = i;
		if (philos->num_philo == 1)
			philos->phi[i]->fork_l = philos->num_philo;
		else
		{
			if (i == 0)
				philos->phi[i]->fork_l = philos->num_philo - 1;
			else
				philos->phi[i]->fork_l = i - 1;
		}
		i++;
	}
}

void	phi_eat(t_philoso *ph)
{
	t_philo			*philos;
	unsigned long	timest;

	philos = ph->philo_data;
	timest = ph->ts;
	pthread_mutex_lock(&philos->chopsticks[ph->fork_r]);
	pthread_mutex_lock(&philos->chopsticks[ph->fork_l]);
	pthread_mutex_lock(&philos->print);
	if (!philos->check)
	{
		printf("%lu %d %s \n", time_() - timest, ph->phi_num, "has taken fork");
		printf("%lu %d %s \n", time_() - timest, ph->phi_num, "has taken fork");
		printf("%lu %d %s \n", time_() - timest, ph->phi_num, "is eating");
	}
	pthread_mutex_unlock(&philos->print);
	t_wait(philos->time_to_eat, philos);
	pthread_mutex_lock(&philos->print);
	ph->last_eat = time_();
	pthread_mutex_unlock(&philos->print);
	ph->num_times_eaten++;
	pthread_mutex_unlock(&philos->chopsticks[ph->fork_l]);
	pthread_mutex_unlock(&philos->chopsticks[ph->fork_r]);
}

void	phi_think(t_philoso *ph)
{
	t_philo			*philos;
	unsigned long	timest;

	philos = ph->philo_data;
	timest = ph->ts;
	pthread_mutex_lock(&philos->print);
	if (!philos->check)
		printf("%lu %d %s \n", time_() - timest, ph->phi_num, "is thinking");
	pthread_mutex_unlock(&philos->print);
}

void	phi_sleep(t_philoso *ph)
{
	t_philo			*philos;
	unsigned long	timest;

	philos = ph->philo_data;
	timest = ph->ts;
	pthread_mutex_lock(&philos->print);
	if (!philos->check)
		printf("%lu %d %s \n", time_() - timest, ph->phi_num, "is sleeping");
	pthread_mutex_unlock(&philos->print);
	t_wait(philos->time_to_sleep, philos);
}

int	phi_died(t_philoso *ph)
{
	t_philo			*philos;

	philos = ph->philo_data;
	pthread_mutex_lock(&philos->print);
	if (!philos->check)
	{
		printf("%lu %d %s\n", time_() - ph->ts, ph->phi_num, "is died");
		philos->check = 1;
	}
	pthread_mutex_unlock(&philos->print);
	return (1);
}
