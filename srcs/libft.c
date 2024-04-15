/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arturo <arturo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 20:35:39 by arturo            #+#    #+#             */
/*   Updated: 2024/04/15 10:55:55 by arturo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	size_calc(long int n)
{
	int	digits;

	digits = 0;
	if (n == 0)
		digits++;
	if (n < 0)
	{
		n *= -1;
		digits++;
	}
	while (n > 0)
	{
		n /= 10;
		digits++;
	}
	return (digits);
}

char	*ft_itoa(int n, char *result)
{
	int		len;
	long	num;

	num = (long)n;
	len = size_calc(num);
	result[len] = '\0';
	if (num == 0)
		result[0] = '0';
	if (num < 0)
	{
		result[0] = '-';
		num *= -1;
	}
	while (num > 0)
	{
		result[--len] = (num % 10) + '0';
		num /= 10;
	}
	return (result);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s || fd < 0 || fd > 1023)
		return ;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}
