/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arturo <arturo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 22:32:29 by arturo            #+#    #+#             */
/*   Updated: 2024/04/15 05:34:06 by arturo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	ft_take_forks(t_philo *philo)
{
	pthread_mutex_lock(&(philo->data->mutex_forks[philo->fork1]));
	pthread_mutex_lock(&(philo->data->mutex_print));
	printf("%llu: philo[%d] has taken fork %d\n", ft_get_time() - philo->data->tm_start, philo->id, philo->fork1);
	pthread_mutex_unlock(&(philo->data->mutex_print));
	pthread_mutex_lock(&(philo->data->mutex_forks[philo->fork2]));
	pthread_mutex_lock(&(philo->data->mutex_print));
	printf("%llu: philo[%d] has taken fork %d\n", ft_get_time() - philo->data->tm_start, philo->id, philo->fork2);
	pthread_mutex_unlock(&(philo->data->mutex_print));
}

void	ft_wait_for_all_threads(t_philo *philo)
{
	if (philo->id % 2)
		usleep(15000);
		//ft_usleep((philo->data->tm_eat - 10), philo->data);
	/*else if (philo->data->total_philo % 2 != 0 \
	&& philo->id == philo->data->total_philo)
		ft_usleep(((philo->data->tm_eat * 2) - 10), philo->data);*/
}

void	ft_release_forks(t_philo *philo)
{
	pthread_mutex_unlock(&(philo->data->mutex_forks[philo->fork1]));
	pthread_mutex_unlock(&(philo->data->mutex_forks[philo->fork2]));
	/*pthread_mutex_lock(&philo->data->mutex_print);
	printf("fork %d is FREE\n", philo->fork1);
	printf("fork %d is FREE\n", philo->fork2);
	pthread_mutex_unlock(&philo->data->mutex_print);*/
}

void	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(&(philo->data->mutex_print));
	printf("%llu: philo[%d] is eating\n", ft_get_time() - philo->data->tm_start, philo->id);
	pthread_mutex_unlock(&(philo->data->mutex_print));
	pthread_mutex_lock(&(philo->data->mutex_meals));
	philo->meals++;
	if (philo->meals >= philo->data->meals_max)
		philo->is_full = TRUE; //should also un;lock and return
	philo->last_meal_tm = ft_get_time();
	pthread_mutex_unlock(&(philo->data->mutex_meals));
	ft_usleep(philo->data->tm_eat, philo->data);
}

void	ft_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mutex_print);
	printf("%llu: philo[%d] is sleeping\n", ft_get_time() - philo->data->tm_start, philo->id);
	pthread_mutex_unlock(&philo->data->mutex_print);
	ft_usleep(philo->data->tm_sleep, philo->data);
}

void	ft_think(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mutex_print);
	printf("%llu: philo[%d] is thinking\n", ft_get_time() - philo->data->tm_start, philo->id);
	pthread_mutex_unlock(&philo->data->mutex_print);
	ft_usleep(philo->data->tm_think, philo->data);
}

void	*group_dinner(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	philo->last_meal_tm = ft_get_time();
	ft_wait_for_all_threads(philo);
	while (1)
	{
		ft_take_forks(philo);
		ft_eat(philo);
		ft_release_forks(philo);
		ft_sleep(philo);
		ft_think(philo);
	}
	return (NULL);
}
