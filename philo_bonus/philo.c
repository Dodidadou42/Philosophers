/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddychus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 18:33:48 by ddychus           #+#    #+#             */
/*   Updated: 2023/01/20 18:33:52 by ddychus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	kill_all(t_var *v, t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < v->nop)
	{
		kill(philo[i].pid, SIGKILL);
		pthread_join(philo[i].thread, NULL);
	}
	sem_close(v->death);
	sem_close(v->end);
	sem_close(v->forks);
	sem_close(v->msg);
}

void	philosophers(t_var *v)
{
	int	i;

	i = 0;
	while (i < v->nop)
	{
		v->philo[i].n = i + 1;
		v->philo[i].v = v;
		v->philo[i].pid = fork();
		if (v->philo[i].pid == 0)
		{
			philo_process(&v->philo[i]);
			exit(0);
		}
		else
			i++;
	}
	sem_wait(v->end);
	kill_all(v, v->philo);
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
	system("leaks philo_bonus");
	return (0);
}
