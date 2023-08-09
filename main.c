/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snagulap <snagulap@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 18:58:10 by snagulap          #+#    #+#             */
/*   Updated: 2023/07/30 16:22:02 by snagulap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*fun_thread(void *arg)
{
	t_philo		*philos;
	t_philoso	*ph;
	int			cond;

	ph = (t_philoso *)arg;
	philos = ph->philo_data;
	if (ph->phi_num % 2 == 0)
		t_wait(philos->time_to_eat, philos);
	pthread_mutex_lock(&philos->print);
	cond = philos->check;
	pthread_mutex_unlock(&philos->print);
	while (!cond && (philos->no_of_times_eaten == 0 || philos->no_of_times_eaten
			> (unsigned long)ph->num_times_eaten) && philos->num_philo != 1)
	{
		phi_eat(ph);
		phi_sleep(ph);
		phi_think(ph);
		pthread_mutex_lock(&philos->print);
		cond = philos->check;
		pthread_mutex_unlock(&philos->print);
	}
	if (philos->num_philo == 1)
		phi_died(ph);
	return (ph);
}

void	mutex_init(t_philo *philo)
{
	unsigned int	i;

	i = 0;
	philo->chopsticks = malloc(sizeof(pthread_mutex_t) * philo->num_philo);
	while (i < philo->num_philo)
	{
		pthread_mutex_init(&philo->chopsticks[i], NULL);
		i++;
	}
	pthread_mutex_init(&philo->print, NULL);
}

void	forking(t_philo *philos)
{
	unsigned int	i;

	i = 0;
	mutex_init(philos);
	while (i < philos->num_philo)
	{
		philos->phi[i]->thread = malloc(sizeof(pthread_t));
		pthread_create(philos->phi[i]->thread, NULL, fun_thread, \
		philos->phi[i]);
		i++;
	}
	i = 0;
	while (i < philos->num_philo)
	{
		pthread_join(*(philos->phi[i]->thread), NULL);
		i++;
	}
}

t_philo	*init_philo(t_philo *philos, int argc, char **argv)
{
	unsigned int	i;

	i = 0;
	philos->num_philo = ft_atoi(argv[1]);
	philos->time_to_die = ft_atoi(argv[2]);
	philos->time_to_eat = ft_atoi(argv[3]);
	philos->time_to_sleep = ft_atoi(argv[4]);
	philos->no_of_times_eaten = 0;
	if (argc == 6)
		philos->no_of_times_eaten = ft_atoi(argv[5]);
	philos->phi = malloc(sizeof(t_philoso *) * philos->num_philo);
	while (i < philos->num_philo)
	{
		philos->phi[i] = malloc(sizeof(t_philoso));
		philos->phi[i]->phi_num = i + 1;
		philos->phi[i]->philo_data = philos;
		philos->phi[i]->ts = time_();
		philos->phi[i]->last_eat = time_();
		philos->phi[i]->num_times_eaten = 0;
		i++;
	}
	return (philos);
}

int	main(int argc, char **argv)
{
	t_philo				*philos;
	unsigned int		i;

	if (argc < 5 || argc > 6)
		error_();
	check__(argv);
	philos = malloc(sizeof(t_philo));
	philos = init_philo(philos, argc, argv);
	philos->check = 0;
	arrange(philos);
	forking(philos);
	i = 0;
	if (any_philosopher_died(philos))
	{
		while (i < philos->num_philo)
		{
			free(philos->phi[i]->thread);
			pthread_mutex_destroy(&philos->chopsticks[i]);
			free(philos->phi[i]);
			i++;
		}
		pthread_mutex_destroy(&philos->print);
		free(philos->phi);
		free(philos);
	}
}
