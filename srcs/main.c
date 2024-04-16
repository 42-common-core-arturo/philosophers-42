/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arturo <arturo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 21:58:53 by arturo            #+#    #+#             */
/*   Updated: 2024/04/17 02:52:20 by arturo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int ac, char **av)
{
	t_data	*data;

	check_input(ac, av);
	data = get_data(av);
	if (data->total_philo == 1)
		dinner_for_one(data);
	start_mutexes(data);
	start_threads(data);
	check_end_dinner(data);
	end_threads(data);
	end_mutexes(data);
	//printf("tm to think %llu\n", data->tm_think);
	free(data);
}
