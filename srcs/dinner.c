/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arturo <arturo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 22:32:29 by arturo            #+#    #+#             */
/*   Updated: 2024/04/15 16:40:37 by arturo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_take_forks(t_philo *philo)
{
	pthread_mutex_lock(&(philo->data->mutex_forks[philo->fork1]));
	pthread_mutex_lock(&(philo->data->mutex_print));
	if (philo->data->end == TRUE)
	{
		pthread_mutex_unlock(&(philo->data->mutex_forks[philo->fork1]));
		pthread_mutex_unlock(&(philo->data->mutex_print));
		return ;
	}
	ft_print(philo, " has taken a fork\n");
	pthread_mutex_unlock(&(philo->data->mutex_print));
	pthread_mutex_lock(&(philo->data->mutex_forks[philo->fork2]));
	pthread_mutex_lock(&(philo->data->mutex_print));
	if (philo->data->end == TRUE)
	{
		pthread_mutex_unlock(&(philo->data->mutex_forks[philo->fork1]));
		pthread_mutex_unlock(&(philo->data->mutex_forks[philo->fork2]));
		pthread_mutex_unlock(&(philo->data->mutex_print));
		return ;
	}
	ft_print(philo, " has taken a fork\n");
	pthread_mutex_unlock(&(philo->data->mutex_print));
}

void	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(&(philo->data->mutex_meals));
	m_print(philo, " is eating\n");
	philo->last_meal_tm = ft_get_time();
	philo->meals++;
	if (philo->data->meals_max != 0 && philo->meals >= philo->data->meals_max)
		philo->is_full = TRUE;
	pthread_mutex_unlock(&(philo->data->mutex_meals));
	ft_usleep(philo->data->tm_eat, philo->data);
	pthread_mutex_unlock(&(philo->data->mutex_forks[philo->fork1]));
	pthread_mutex_unlock(&(philo->data->mutex_forks[philo->fork2]));
}

void	ft_sleep(t_philo *philo)
{
	m_print(philo, " is sleeping\n");
	ft_usleep(philo->data->tm_sleep, philo->data);
	m_print(philo, " is thinking\n");
	ft_usleep(philo->data->tm_think, philo->data);
}

void	ft_prep(t_philo *philo)
{
	pthread_mutex_lock(&(philo->data->mutex_meals));
	philo->last_meal_tm = ft_get_time();
	pthread_mutex_unlock(&(philo->data->mutex_meals));
	if (philo->id % 2)
		ft_usleep(philo->data->tm_eat - 5, philo->data);
}

void	*group_dinner(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	ft_prep(philo);
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
		pthread_mutex_lock(&(philo->data->mutex_meals));
		if (philo->is_full == TRUE)
		{
			pthread_mutex_unlock(&(philo->data->mutex_meals));
			return (NULL);
		}
		pthread_mutex_unlock(&(philo->data->mutex_meals));
		ft_sleep(philo);
	}
	return (NULL);
}
