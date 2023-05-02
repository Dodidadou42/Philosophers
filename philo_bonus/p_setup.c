/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_setup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddychus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 18:33:18 by ddychus           #+#    #+#             */
/*   Updated: 2023/01/20 18:33:20 by ddychus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_v(int argc, char **argv, t_var *v)
{
	int	i;

	sem_unlink("/forks");
	sem_unlink("/death");
	sem_unlink("/end");
	sem_unlink("/msg");
	i = -1;
	gettimeofday(&v->start, NULL);
	v->death = 0;
	v->nop = ft_atoi(argv[1]);
	v->ttd = ft_atoi(argv[2]);
	v->tte = ft_atoi(argv[3]);
	v->tts = ft_atoi(argv[4]);
	if (argc == 6)
		v->eat = ft_atoi(argv[5]);
	else
		v->eat = -1;
	v->forks = sem_open("/forks", O_CREAT, 0600, v->nop);
	v->death = sem_open("/death", O_CREAT, 0600, 1);
	v->end = sem_open("/end", O_CREAT, 0600, 1);
	v->msg = sem_open("/msg", O_CREAT, 0600, 1);
	sem_wait(v->end);
	v->philo = malloc(sizeof(t_philo) * v->nop);
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
