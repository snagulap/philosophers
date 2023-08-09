/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snagulap <snagulap@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 18:51:40 by snagulap          #+#    #+#             */
/*   Updated: 2023/07/29 18:44:52 by snagulap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	j;
	int	a_i;

	i = 0;
	j = 1;
	a_i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == ' '))
		i++;
	if (str[i] == '-')
		j = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		a_i = (a_i * 10) + (str[i] - '0');
		i++;
	}
	return (a_i * j);
}

unsigned long	time_(void)
{
	struct timeval	ti;

	gettimeofday(&ti, NULL);
	return ((ti.tv_sec * 1000) + (ti.tv_usec / 1000));
}

void	t_wait(unsigned long time__, t_philo *philos)
{
	unsigned long	misnd;

	misnd = time_();
	while (time_() < (time__ + misnd) && !any_philosopher_died(philos))
		usleep(50);
}

int	min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

int	any_philosopher_died(t_philo *philos)
{
	unsigned int	i;
	unsigned long	t;

	i = 0;
	while (i < philos->num_philo)
	{
		pthread_mutex_lock(&philos->print);
		t = philos->phi[i]->last_eat;
		pthread_mutex_unlock(&philos->print);
		if ((time_() - t)
			>= (unsigned long)(philos->time_to_die))
			return (phi_died(philos->phi[i]));
		i++;
	}
	return (0);
}
