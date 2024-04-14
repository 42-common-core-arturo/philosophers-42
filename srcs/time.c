/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arturo <arturo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 20:54:12 by artclave          #+#    #+#             */
/*   Updated: 2024/04/14 23:03:50 by arturo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_long	ft_get_time(void)
{
	struct timeval	now;
	t_long			result;

	gettimeofday(&now, NULL);
	result = now.tv_sec * 1000ULL + now.tv_usec / 1000;
	return (result);
}

void	ft_usleep(t_long total, t_data *data)
{
	t_long	end;
	t_long	remaining;

	(void)data;
	end = ft_get_time() + total;
	remaining = end - ft_get_time();
	while (remaining > 0)
	{
		//if (m_read_int(&data->end, &data->mutex_end) == TRUE)
		//	return ;
		remaining = end - ft_get_time();
		if (remaining > 10000)
			usleep(10000);
		else if (remaining > 1000)
			usleep(1000);
		else if (remaining > 100)
			usleep(100);
		else if (remaining > 0)
			usleep(10);
	}
}
