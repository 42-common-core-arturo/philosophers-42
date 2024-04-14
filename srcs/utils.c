/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arturo <arturo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 22:02:46 by arturo            #+#    #+#             */
/*   Updated: 2024/04/15 03:51:01 by arturo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/**
 * @brief calls clean function, prints error message and exits
 * 
 * @param clean clean list
 * @param error_code exit code and also type of error
 */
void	ft_exit(int error_code)
{
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
