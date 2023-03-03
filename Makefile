SRCS = srcs/main.c 

CC = gcc

FLAGS = -Werror -Wall -Wextra

INCLUDE = includes

OBJS = ${SRCS:.c=.o}

NAME = philo

.c.o:
			${CC} ${FLAGS} -c $< -o ${<:.c=.o}

${NAME}:	${OBJS}
			make -C libft
			${CC} ${FLAGS} -o ${NAME} ${OBJS} -I ${INCLUDE} -lft -Llibft

all: ${NAME}

clean:
			${RM} ${OBJS}
			make clean -C libft

fclean:		clean
			${RM} ${NAME}
			make fclean -C libft

re:			fclean all

.PHONY:		all clean fclean re