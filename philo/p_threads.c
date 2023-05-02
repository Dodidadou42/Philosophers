/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_threads.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddychus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 15:46:12 by ddychus           #+#    #+#             */
/*   Updated: 2023/04/05 15:46:14 by ddychus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_end(t_var *v)
{
	int	ret;

	pthread_mutex_lock(&v->mutex_death);
	if (v->end == 1)
		ret = 1;
	else
		ret = 0;
	pthread_mutex_unlock(&v->mutex_death);
	return (ret);
}

int	take_forks(t_philo *philo, t_var *v)
{
	if (!check_end(v))
		pthread_mutex_lock(&philo->v->mutex_forks[philo->n - 1]);
	else
		return (0);
	message(philo->v, "has taken a fork", philo->n);
	if (philo->v->args[0] != 1 && !check_end(v))
	{
		if (philo->n == philo->v->args[0])
			pthread_mutex_lock(&philo->v->mutex_forks[0]);
		else if (philo->n != philo->v->args[0])
			pthread_mutex_lock(&philo->v->mutex_forks[philo->n]);
		message(philo->v, "has taken a fork", philo->n);
	}
	else if (check_end(v) || philo->v->args[0] == 1)
		return (0);
	return (1);
}

int	eat_and_sleep(t_philo *philo, t_var *v)
{
	gettimeofday(&philo->last_meal, NULL);
	message(philo->v, "is eating", philo->n);
	philo->meals++;
	if (!check_end(v))
		ft_sleep(philo->v->args[2], philo->v);
	else
		return (0);
	pthread_mutex_unlock(&philo->v->mutex_forks[philo->n - 1]);
	if (philo->n == philo->v->args[0])
		pthread_mutex_unlock(&philo->v->mutex_forks[0]);
	else
		pthread_mutex_unlock(&philo->v->mutex_forks[philo->n]);
	if (philo->meals == philo->v->args[4])
		philo->done_eating = 1;
	else
	{
		message(philo->v, "is sleeping", philo->n);
		ft_sleep(philo->v->args[3], philo->v);
		message(philo->v, "is thinking", philo->n);
	}
	return (1);
}

void	philo_routine(t_philo *philo, t_var *v)
{
	if (!philo->done_eating)
	{
		if (!take_forks(philo, v))
			return ;
		if (!eat_and_sleep(philo, v))
			return ;
	}
	if (philo->done_eating == 1)
	{
		message(philo->v, "is done eating", philo->n);
		v->all_done++;
		return ;
	}
	else if (check_end(v))
		return ;
	philo_routine(philo, v);
}

void	*philo_threads(void *pointer)
{
	t_philo		*philo;

	philo = (t_philo *)pointer;
	gettimeofday(&philo->last_meal, NULL);
	philo->meals = 0;
	philo->done_eating = 0;
	if (philo->v->args[4] == 0)
		philo->done_eating = 1;
	if (philo->n % 2 == 0)
		ft_sleep(philo->v->args[2], philo->v);
	philo_routine(philo, philo->v);
	return (NULL);
}
