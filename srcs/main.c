/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arturo <arturo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 21:58:53 by arturo            #+#    #+#             */
/*   Updated: 2024/04/15 05:28:33 by arturo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int ac, char **av)
{
	t_data	*data;

	check_input(ac, av);
	data = get_data(av);
	start_mutexes(data);
	//printf("check\n");
	start_threads(data);
	check_end_dinner(data);
	end_threads(data);
	end_mutexes(data);
	free(data);
}
