/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_setup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddychus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 15:21:02 by ddychus           #+#    #+#             */
/*   Updated: 2023/01/18 15:21:05 by ddychus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_v(int argc, char **argv, t_var *v)
{
	int	i;

	i = -1;
	gettimeofday(&v->start, NULL);
	v->end = 0;
	v->args[0] = ft_atoi(argv[1]);
	v->args[1] = ft_atoi(argv[2]);
	v->args[2] = ft_atoi(argv[3]);
	v->args[3] = ft_atoi(argv[4]);
	v->all_done = 0;
	if (argc == 6)
		v->args[4] = ft_atoi(argv[5]);
	else
		v->args[4] = -1;
	v->mutex_forks = malloc(sizeof(pthread_mutex_t) * v->args[0]);
	while (++i < v->args[0])
		pthread_mutex_init(&v->mutex_forks[i], NULL);
	pthread_mutex_init(&v->mutex_death, NULL);
	pthread_mutex_init(&v->mutex_message, NULL);
	v->philo = malloc(sizeof(t_philo) * v->args[0]);
}

void	check_args(char **argv)
{
	int			i;
	long long	n;

	i = 0;
	while (argv[++i])
	{
		if (!is_num(argv[i]))
			error("Error\nArguments must be numbers only.");
		n = ft_atoi(argv[i]);
		if (i == 1 && n < 1)
			error("Error\nThere must be at least one pilosopher.");
		if (n > INT_MAX)
			error("Error\nInt Overflow.");
		if (n < 0)
			error("Error\nArguments cannot be negative.");
	}
}
