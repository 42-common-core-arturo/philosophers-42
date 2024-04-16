/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arturo <arturo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 22:00:13 by arturo            #+#    #+#             */
/*   Updated: 2024/04/17 02:52:28 by arturo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/// @brief initialize data struct
/// @param data struct to initialize/update
/// @param av array of strings from main input
void	init_data(t_data *data, char **av)
{
	long long tm_left;

	data->tm_start = ft_get_time();
	data->total_philo = ft_atoi_long(av[1]);
	if (data->total_philo < 1)
		ft_exit(INPUT_ERROR, NULL);
	data->end = FALSE;
	data->tm_die = ft_atoi_long(av[2]);
	data->tm_eat = ft_atoi_long(av[3]);
	data->tm_sleep = ft_atoi_long(av[4]);
	tm_left = ((data->tm_die - (data->tm_sleep + data->tm_sleep)) * 0.5);
	data->tm_think = ((data->tm_die - (data->tm_sleep + data->tm_sleep)) * 0.5);
	if (tm_left < 0)
		data->tm_think = 0;
	//printf("tm to think %llu\ntm left: %lld\n\n", data->tm_think, tm_left);
	data->meals_max = 0;
	if (av[5])
		data->meals_max = ft_atoi_long(av[5]);
}

/// @brief initialize philo struct
/// @param data struct holding array of philo structures
void	init_philo(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->total_philo)
	{
		data->philo[i].id = i + 1;
		data->philo[i].fork1 = i - (i % 2);
		data->philo[i].fork2 = i - 1 + (i % 2);
		if (data->philo[i].fork2 < 0)
			data->philo[i].fork2 = data->total_philo - 1;
		data->philo[i].thread = 0;
		data->philo[i].meals = 0;
		data->philo[i].last_meal_tm = data->tm_start;
		data->philo[i].is_full = FALSE;
		data->philo[i].data = data;
	}
}

/// @brief initialize data struct and philo structs
/// @param av array of arguments from main
/// @return new data struct
t_data	*get_data(char **av)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		ft_exit(MALLOC_ERROR, NULL);
	init_data(data, av);
	init_philo(data);
	return (data);
}

/// @brief checks if user input is valid :
//1.total of 5 or 6 parameters
//2.only positive numbers, bigger than 0
//3.sleep, eating and death times >= 60
/// @param ac amount of arguments from main
/// @param av array of arguments from main
void	check_input(int ac, char **av)
{
	int		i;
	t_long	num;

	if (ac != 5 && ac != 6)
		ft_exit(AC_ERROR, NULL);
	i = 0;
	while (++i < ac)
	{
		num = ft_atoi_long(av[i]);
		if (((i < 5) && i > 1 && (int)num < MIN_TIME)
			|| (i == 1 && ((int)num < 1 || (int)num > 200)))
			ft_exit(INPUT_ERROR, NULL);
	}
}
