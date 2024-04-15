/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arturo <arturo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 22:41:51 by arturo            #+#    #+#             */
/*   Updated: 2024/04/15 10:58:19 by arturo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	is_dead(t_philo *philo, t_data *data)
{
	char	str[100];

	if (ft_get_time() - philo->last_meal_tm < data->tm_die)
		return (FALSE);
	pthread_mutex_lock(&(philo->data->mutex_print));
	philo->data->end = TRUE;
	ft_putstr_fd(ft_itoa((int)(ft_get_time() - philo->data->tm_start), str), 1);
	ft_putstr_fd(" ", 1);
	ft_putstr_fd(ft_itoa((int)philo->id, str), 1);
	ft_putstr_fd(" died\n", 1);
	pthread_mutex_unlock(&(philo->data->mutex_print));
	return (TRUE);
}

/// @brief main thread checks if any philo is dead or if all are full 
/// @param data 
void	check_end_dinner(t_data *data)
{
	int	i;
	int	all_full;

	all_full = 0;
	while (all_full < data->total_philo)
	{
		i = -1;
		all_full = 0;
		while (++i < data->total_philo)
		{
			pthread_mutex_lock(&(data->mutex_meals));
			if (data->philo[i].is_full == TRUE)
				all_full++;
			else if (is_dead(&data->philo[i], data) == TRUE)
			{
				pthread_mutex_unlock(&(data->mutex_meals));
				return ;
			}
			pthread_mutex_unlock(&(data->mutex_meals));
			if (all_full == data->total_philo)
				return ;
			usleep(1000);
		}
	}
}
