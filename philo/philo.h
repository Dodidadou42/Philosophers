/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddychus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 15:21:35 by ddychus           #+#    #+#             */
/*   Updated: 2023/01/18 15:21:37 by ddychus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <time.h>
# include <string.h>
# include <limits.h>
# include <sys/time.h>

typedef struct s_philo
{
	pthread_t		thread;

	int				n;
	int				meals;
	int				done_eating;

	struct timeval	last_meal;

	struct s_var	*v;

}	t_philo;

typedef struct s_var
{
	int				end;
	int				all_done;

	int				args[5];

	t_philo			*philo;

	pthread_mutex_t	mutex_death;
	pthread_mutex_t	mutex_message;
	pthread_mutex_t	*mutex_forks;

	struct timeval	start;
}	t_var;

// PHILOSOPHER
void		init_v(int argc, char **argv, t_var *v);
void		check_args(char **argv);
void		*philo_threads(void *pointer);
int			is_alive(t_philo *phil);

// UTILS
void		ft_sleep(int n, t_var *v);
void		error(char *str);
int			is_num(char *str);
void		message(t_var *v, char *msg, int n);

// LIBFT
void		ft_putstr_fd(char *s, int fd);
size_t		ft_strlen(const char *str);
long long	ft_atoi(char *s);
int			ft_strcmp(char *str1, char *str2);

#endif
