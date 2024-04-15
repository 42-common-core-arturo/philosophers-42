/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arturo <arturo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 22:32:29 by arturo            #+#    #+#             */
/*   Updated: 2024/04/15 09:00:24 by arturo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_release_forks(t_philo *philo)
{
	pthread_mutex_unlock(&(philo->data->mutex_forks[philo->fork1]));
	pthread_mutex_unlock(&(philo->data->mutex_forks[philo->fork2]));
}

void	ft_take_forks(t_philo *philo)
{
	pthread_mutex_lock(&(philo->data->mutex_forks[philo->fork1]));
	//m_print(philo, "has taken a fork\n");
	pthread_mutex_lock(&(philo->data->mutex_print));
	if (philo->data->end == TRUE)
	{
		pthread_mutex_unlock(&(philo->data->mutex_forks[philo->fork1]));
		pthread_mutex_unlock(&(philo->data->mutex_print));
		return ;
	}
	printf("%llu %d %s", (ft_get_time() - philo->data->tm_start), philo->id, "has taken a fork\n");
	pthread_mutex_unlock(&(philo->data->mutex_print));
	pthread_mutex_lock(&(philo->data->mutex_forks[philo->fork2]));
	//m_print(philo, "has taken a fork\n");
	pthread_mutex_lock(&(philo->data->mutex_print));
	if (philo->data->end == TRUE)
	{
		ft_release_forks(philo);
		pthread_mutex_unlock(&(philo->data->mutex_print));
		return ;
	}
	printf("%llu %d %s", (ft_get_time() - philo->data->tm_start), philo->id, "has taken a fork\n");
	pthread_mutex_unlock(&(philo->data->mutex_print));
}

void	ft_wait_for_all_threads(t_philo *philo)
{
	if (philo->id % 2)
		usleep(15000);
}

void	ft_eat(t_philo *philo)
{
	m_print(philo, " is eating\n");
	pthread_mutex_lock(&(philo->data->mutex_meals));
	philo->meals++;
	philo->last_meal_tm = ft_get_time();
	if (philo->data->meals_max != 0 && philo->meals >= philo->data->meals_max)
	{
		m_print(philo, "is full\n\n");
		philo->is_full = TRUE;
	}
	pthread_mutex_unlock(&(philo->data->mutex_meals));
	ft_usleep(philo->data->tm_eat, philo->data);
}

void	ft_sleep(t_philo *philo)
{
	m_print(philo, " is sleeping\n");
	ft_usleep(philo->data->tm_sleep, philo->data);
}

void	ft_think(t_philo *philo)
{
	m_print(philo, " is thinking\n");
	ft_usleep(philo->data->tm_think, philo->data);
}

void	*group_dinner(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	pthread_mutex_lock(&(philo->data->mutex_meals));
	philo->last_meal_tm = ft_get_time();
	pthread_mutex_unlock(&(philo->data->mutex_meals));
	ft_wait_for_all_threads(philo);
	while (1)
	{
		ft_take_forks(philo);
		pthread_mutex_lock(&(philo->data->mutex_print));
		if (philo->data->end == TRUE)
		{
			pthread_mutex_unlock(&(philo->data->mutex_print));
			return (NULL);
		}
		pthread_mutex_unlock(&(philo->data->mutex_print));
		ft_eat(philo);
		ft_release_forks(philo);
		pthread_mutex_lock(&(philo->data->mutex_meals));
		if (philo->is_full == TRUE)
		{
			pthread_mutex_unlock(&(philo->data->mutex_meals));
			return (NULL);
		}
		pthread_mutex_unlock(&(philo->data->mutex_meals));
		ft_sleep(philo);
		ft_think(philo);
	}
	return (NULL);
}
