/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arturo <arturo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 22:14:50 by arturo            #+#    #+#             */
/*   Updated: 2024/04/15 16:42:30 by arturo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	start_threads(t_data *data)
{
	int	i;

	i = -1;
	pthread_mutex_lock(&(data->mutex_meals));
	while (++i < data->total_philo)
	{
		if (pthread_create(&(data->philo[i].thread), NULL, group_dinner, \
		(void *)&(data->philo[i])) != 0)
			ft_exit(THREAD_ERROR, data);
	}
	pthread_mutex_unlock(&(data->mutex_meals));
}

void	end_threads(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->total_philo)
	{
		if (pthread_join(data->philo[i].thread, NULL) != 0)
			ft_exit(THREAD_ERROR, data);
	}
}
