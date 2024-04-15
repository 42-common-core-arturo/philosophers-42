/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arturo <arturo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 22:02:46 by arturo            #+#    #+#             */
/*   Updated: 2024/04/15 10:53:35 by arturo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/**
 * @brief calls clean function, prints error message and exits
 * 
 * @param clean clean list
 * @param error_code exit code and also type of error
 */
void	ft_exit(int error_code, t_data *data)
{
	if (data)
		free(data);
	if (error_code == AC_ERROR)
		ft_putstr_fd("Invalid number of arguments\n", 2);
	if (error_code == INPUT_ERROR)
		ft_putstr_fd("Invalid numerical values\n", 2);
	if (error_code == MALLOC_ERROR)
		ft_putstr_fd("Malloc failure\n", 2);
	if (error_code == MUTEX_ERROR)
		ft_putstr_fd("Mutex failed\n", 2);
	if (error_code == THREAD_ERROR)
		ft_putstr_fd("Thread failed\n", 2);
	exit(error_code);
}

/**
 * @brief converts string to long long num
 * 
 * @param str
 */
long long	ft_atoi_long(char *str)
{
	int			i;
	long long	num;

	num = 0;
	i = 0;
	if (!str)
		return (0);
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	if (str[i] && str[i] == '+')
		i++;
	if (!str[i] && str[i] < '0' && str[i] > '9')
		return (-1);
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = (num * 10) + str[i] - '0';
		i++;
	}
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] || num <= 0)
		return (-1);
	return (num);
}

void	dinner_for_one(t_data *data)
{
	pthread_mutex_init(&(data->mutex_print), NULL);
	m_print(&data->philo[0], " has taken a fork\n");
	while (1)
	{
		if (is_dead(&(data->philo[0]), data) == TRUE)
			break ;
	}
	pthread_mutex_destroy(&(data->mutex_print));
	ft_exit(EXIT_SUCCESS, data);
}

void	ft_print(t_philo *philo, char *message)
{
	char	str[100];

	if (philo->data->end == TRUE)
	{
		pthread_mutex_unlock(&(philo->data->mutex_print));
		return ;
	}
	ft_putstr_fd(ft_itoa((int)(ft_get_time() - philo->data->tm_start), str), 1);
	ft_putstr_fd(" ", 1);
	ft_putstr_fd(ft_itoa((int)philo->id, str), 1);
	ft_putstr_fd(message, 1);
}
