/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arturo <arturo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 22:41:51 by arturo            #+#    #+#             */
/*   Updated: 2024/04/15 05:26:21 by arturo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	is_dead(t_philo *philo, t_data *data)
{
	if (ft_get_time() - philo->last_meal_tm < data->tm_die)
	{
		pthread_mutex_unlock(&(data->mutex_meals));
		return (FALSE);
	}
	pthread_mutex_unlock(&(data->mutex_meals));
	pthread_mutex_lock(&(data->mutex_end));
	philo->data->end = TRUE;
	pthread_mutex_unlock(&(data->mutex_end));
	pthread_mutex_lock(&(data->mutex_print));
	printf("\n%llu PHILO [%d] IS DEAD!!!\n\n", ft_get_time() - philo->data->tm_start, philo->id);
	return (TRUE);
}

/// @brief main thread checks if any philo is dead or if all are full 
/// @param data 
void	check_end_dinner(t_data *data)
{
	int	i;
	//int	all_full;

//	all_full = 0; 
	//while (all_full < data->total_philo)
	while (1)
	{
		i = -1;
		//all_full = 0;
		while (++i < data->total_philo)
		{
			pthread_mutex_lock(&(data->mutex_meals));
			/*if (data->philo[i].is_full == TRUE)
			{
				pthread_mutex_unlock(&data->mutex_meals[i]);
				all_full++;
			}
			else */if (is_dead(&data->philo[i], data) == TRUE)
				return ;
			usleep(1000);
		}
	}
	pthread_mutex_lock(&(data->mutex_print));
}
