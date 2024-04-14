/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutexes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arturo <arturo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 22:04:26 by arturo            #+#    #+#             */
/*   Updated: 2024/04/15 05:20:24 by arturo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	start_mutexes(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->total_philo)
	{
		if (pthread_mutex_init(&(data->mutex_forks[i]), NULL) != 0)
			ft_exit(MUTEX_ERROR);
	}
	if (pthread_mutex_init(&(data->mutex_meals), NULL) != 0)
		ft_exit(MUTEX_ERROR);
	if (pthread_mutex_init(&(data->mutex_print), NULL) != 0)
		ft_exit(MUTEX_ERROR);
	if (pthread_mutex_init(&(data->mutex_end), NULL) != 0)
		ft_exit(MUTEX_ERROR);
}

void	end_mutexes(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->total_philo)
	{
		if (pthread_mutex_destroy(&(data->mutex_forks[i])) != 0)
			ft_exit(MUTEX_ERROR);
	}
	if (pthread_mutex_destroy(&(data->mutex_meals)) != 0)
		ft_exit(MUTEX_ERROR);
	pthread_mutex_unlock(&(data->mutex_print));
	if (pthread_mutex_destroy(&(data->mutex_print)) != 0)
		ft_exit(MUTEX_ERROR);
	if (pthread_mutex_destroy(&(data->mutex_end)) != 0)
		ft_exit(MUTEX_ERROR);
}
