/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arturo <arturo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 22:14:50 by arturo            #+#    #+#             */
/*   Updated: 2024/04/15 08:03:54 by arturo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	start_threads(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->total_philo)
	{
		if (pthread_create(&(data->philo[i].thread), NULL, group_dinner, \
		(void *)&(data->philo[i])) != 0)
			ft_exit(THREAD_ERROR, data);
		//if (pthread_detach(data->philo[i].thread) != 0)
		//	ft_exit(THREAD_ERROR, data);
	}
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
