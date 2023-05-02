/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddychus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 15:21:27 by ddychus           #+#    #+#             */
/*   Updated: 2023/01/18 15:21:29 by ddychus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_death(t_var *v)
{
	int				i;
	struct timeval	end;
	long			time;

	while (42)
	{
		i = -1;
		while (++i < v->args[0])
		{
			usleep(10);
			gettimeofday(&end, NULL);
			time = ((end.tv_sec - v->philo[i].last_meal.tv_sec) * 1000)
				+ ((end.tv_usec - v->philo[i].last_meal.tv_usec) / 1000);
			if (time >= v->args[1] && v->all_done != v->args[0])
			{
				message(v, "died", v->philo[i].n);
				pthread_mutex_lock(&v->mutex_death);
				v->end = 1;
				pthread_mutex_unlock(&v->mutex_death);
				return ;
			}
			else if (v->all_done == v->args[0])
				return ;
		}
	}
}

void	philosophers(t_var *v)
{
	int	i;

	i = -1;
	while (++i < v->args[0])
	{
		v->philo[i].n = i + 1;
		v->philo[i].v = v;
		if (pthread_create(&v->philo[i].thread, NULL,
				philo_threads, &v->philo[i]))
			error("Error\nCouldn't create thread.");
	}
	ft_sleep(v->args[1], v);
	i = -1;
	check_death(v);
	while (++i < v->args[0])
		pthread_join(v->philo[i].thread, NULL);
	pthread_mutex_destroy(&v->mutex_death);
	pthread_mutex_destroy(v->mutex_forks);
	pthread_mutex_destroy(&v->mutex_message);
	free(v->philo);
}

int	main(int argc, char **argv)
{
	t_var	v;

	if (argc != 6 && argc != 5)
		error("Invalid arguments quantity.");
	else
	{
		check_args(argv);
		init_v(argc, argv, &v);
		philosophers(&v);
	}
	system("leaks philo");
	return (0);
}
