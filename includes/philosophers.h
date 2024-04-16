/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arturo <arturo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 16:30:13 by artclave          #+#    #+#             */
/*   Updated: 2024/04/17 02:51:52 by arturo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

// -- LIBRARIES --
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

// -- GENERAL DEFINES --
# define TRUE 1
# define FALSE 0
# define MIN_TIME 60
# define FREE 0
# define TAKEN 1
# define CONTINUE_DINNER 0
# define END_DINNER 1

// -- ERROR DEFINES --
# define AC_ERROR 1
# define INPUT_ERROR 2
# define MALLOC_ERROR 3
# define MUTEX_ERROR 4
# define THREAD_ERROR 5

//-- MUTEX DEFINES --
# define END 0
# define PRINT 1
# define READY 2
# define NON_FORK_MUTEX 3

// -- STRUCTURES --
typedef unsigned long long		t_long;
typedef struct s_timeval		t_timeval;

typedef struct s_philo
{
	int				id;
	int				fork1;
	int				fork2;
	pthread_t		thread;
	t_long			meals;
	t_long			last_meal_tm;
	int				is_full;
	struct s_data	*data;
}		t_philo;

typedef struct s_data
{
	pthread_mutex_t	mutex_forks[200];
	pthread_mutex_t	mutex_meals;
	pthread_mutex_t	mutex_print;
	int				end;
	int				total_philo;
	t_long			tm_die;
	t_long			tm_eat;
	t_long			tm_sleep;
	t_long			tm_think;
	t_long			tm_start;
	t_long			meals_max;
	t_philo			philo[200];
}		t_data;

void		check_input(int ac, char **av);
t_data		*get_data(char **av);
void		ft_exit(int error_code, t_data *data);
long long	ft_atoi_long(char *str);
void		start_mutexes(t_data *data);
void		end_mutexes(t_data *data);
void		start_threads(t_data *data);
void		end_threads(t_data *data);
t_long		ft_get_time(void);
void		ft_usleep(t_long total, t_data *data);
void		*group_dinner(void *args);
char		*ft_itoa(int n, char *result);
void		ft_putstr_fd(char *s, int fd);
void		check_end_dinner(t_data *data);
int			is_dead(t_philo *philo, t_data *data);
void		dinner_for_one(t_data *data);
void		m_print(t_philo *philo, char *message);
void		ft_print(t_philo *philo, char *message);

#endif