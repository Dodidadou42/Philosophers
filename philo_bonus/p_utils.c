/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddychus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 18:33:36 by ddychus           #+#    #+#             */
/*   Updated: 2023/01/20 18:33:38 by ddychus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_sleep(int n, t_var *v)
{
	struct timeval	time;
	long			t_start;
	long			t_act;

	if (!n)
		usleep(100);
	else
	{
		gettimeofday(&time, NULL);
		t_start = ((time.tv_sec - v->start.tv_sec) * 1000
				+ (time.tv_usec - v->start.tv_usec) / 1000);
		t_act = t_start;
		while (t_act < t_start + n)
		{
			usleep(10);
			gettimeofday(&time, NULL);
			t_act = ((time.tv_sec - v->start.tv_sec) * 1000
					+ (time.tv_usec - v->start.tv_usec) / 1000);
		}
	}
}

void	error(char *str)
{
	if (ft_strlen(str) > 1)
		ft_putstr_fd(str, 2);
	exit(EXIT_FAILURE);
}

int	is_num(char *str)
{
	while (*str)
	{
		if ((*str < '0' || *str > '9') && *str != '-')
			return (0);
		str++;
	}
	return (1);
}

void	message(t_var *v, char *msg, int n)
{
	struct timeval	end;
	long			time;

	sem_wait(v->msg);
	gettimeofday(&end, NULL);
	time = ((end.tv_sec - v->start.tv_sec) * 1000)
		+ ((end.tv_usec - v->start.tv_usec) / 1000);
	printf("%dms %d %s\n", (int)time, n, msg);
	if (ft_strcmp(msg, "died") != 0)
		sem_post(v->msg);
	else
		sem_post(v->end);
}

int	is_alive(t_philo *phil)
{
	struct timeval	end;
	long			time;

	gettimeofday(&end, NULL);
	time = ((end.tv_sec - phil->last_meal.tv_sec) * 1000)
		+ ((end.tv_usec - phil->last_meal.tv_usec) / 1000);
	if (time >= phil->v->ttd)
		return (0);
	else
		return (1);
}
