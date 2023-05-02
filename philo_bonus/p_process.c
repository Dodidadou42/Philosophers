/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_process.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddychus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 18:32:59 by ddychus           #+#    #+#             */
/*   Updated: 2023/01/20 18:33:01 by ddychus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_philo *philo)
{
	sem_wait(philo->v->forks);
	message(philo->v, "has taken a fork", philo->n);
	sem_wait(philo->v->forks);
	message(philo->v, "has taken a fork", philo->n);
}

void	eat_and_sleep(t_philo *philo)
{
	message(philo->v, "is eating", philo->n);
	gettimeofday(&philo->last_meal, NULL);
	philo->meals++;
	ft_sleep(philo->v->tte, philo->v);
	sem_post(philo->v->forks);
	sem_post(philo->v->forks);
	if (philo->meals == philo->v->eat)
	{
		philo->done_eating = 1;
		return ;
	}
	message(philo->v, "is sleeping", philo->n);
	ft_sleep(philo->v->tts, philo->v);
	message(philo->v, "is thinking", philo->n);
}

void	*check_end(void *pointer)
{
	t_philo	*philo;

	philo = (t_philo *)pointer;
	while (1)
	{
		sem_wait(philo->v->death);
		if (!is_alive(philo))
		{
			message(philo->v, "died", philo->n);
			break ;
		}
		if (philo->done_eating == 1)
		{
			message(philo->v, "is done eating", philo->n);
			sem_post(philo->v->death);
			break ;
		}
		sem_post(philo->v->death);
	}
	return (NULL);
}

void	philo_process(t_philo *philo)
{
	gettimeofday(&philo->last_meal, NULL);
	philo->meals = 0;
	philo->done_eating = 0;
	pthread_create(&philo->thread, NULL, check_end, philo);
	if (philo->v->eat == 0)
		philo->done_eating = 1;
	else
	{
		if (philo->n % 2 == 0)
			ft_sleep(10, philo->v);
		while (1)
		{
			take_forks(philo);
			eat_and_sleep(philo);
			if (philo->done_eating == 1)
				break ;
		}
	}
	if (philo->v->eat == 0)
		usleep(1000 * philo->v->nop);
	else
		usleep(philo->v->nop * (philo->v->tte + philo->v->tts) * 300);
	sem_post(philo->v->end);
}
