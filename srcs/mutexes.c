/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutexes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arturo <arturo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 22:04:26 by arturo            #+#    #+#             */
/*   Updated: 2024/04/15 09:20:56 by arturo           ###   ########.fr       */
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
			ft_exit(MUTEX_ERROR, data);
	}
	if (pthread_mutex_init(&(data->mutex_meals), NULL) != 0)
		ft_exit(MUTEX_ERROR, data);
	if (pthread_mutex_init(&(data->mutex_print), NULL) != 0)
		ft_exit(MUTEX_ERROR, data);
}

void	end_mutexes(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->total_philo)
	{
		if (pthread_mutex_destroy(&(data->mutex_forks[i])) != 0)
			ft_exit(MUTEX_ERROR, data);
	}
	if (pthread_mutex_destroy(&(data->mutex_meals)) != 0)
		ft_exit(MUTEX_ERROR, data);
	if (pthread_mutex_destroy(&(data->mutex_print)) != 0)
		ft_exit(MUTEX_ERROR, data);
}

void	m_print(t_philo *philo, char *message)
{
	char	str[100];

	pthread_mutex_lock(&(philo->data->mutex_print));
	if (philo->data->end == TRUE)
	{
		pthread_mutex_unlock(&(philo->data->mutex_print));
		return ;
	}
	ft_putstr_fd(ft_itoa((int)(ft_get_time() - philo->data->tm_start), str), 1);
	ft_putstr_fd(" ", 1);
	ft_putstr_fd(ft_itoa((int)philo->id, str), 1);
	ft_putstr_fd(message, 1);
	pthread_mutex_unlock(&(philo->data->mutex_print));
}
