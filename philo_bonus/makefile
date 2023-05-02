NAME 		= philo_bonus

SRCS 		= ./p_setup.c ./p_process.c ./p_utils.c ./philo.c \
			./libft/ft_atoi.c ./libft/ft_putstr_fd.c \
			./libft/ft_strcmp.c ./libft/ft_strlen.c

INCLUDES	= ./philo.h
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror

RM 			= rm -f

.c.o:
		${CC} ${CFLAGS} -I ${INCLUDES} -c $< -o ${<:.c=.o} 

OBJS		= ${SRCS:.c=.o}

${NAME}:	${OBJS}
			${CC} -o ${NAME} ${OBJS}

all:	${NAME}

clean:
		${RM} ${OBJS}

fclean:	clean
		${RM} ${NAME} 

re:		fclean all

.PHONY:	all clean fclean re