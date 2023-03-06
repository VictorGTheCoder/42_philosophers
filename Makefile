SRCS	=	srcs/main.c srcs/philo_routine.c srcs/philo_utils.c \
			srcs/philo_init.c srcs/philo_actions.c

OBJS	= ${SRCS:.c=.o}

CFLAGS	=  -Wall -Werror -Wextra

CC		= gcc

RM		= rm -f

NAME 	= philo

INCLUDE = includes

#$@ = all, $< = server / client

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o ${<:.c=.o}

$(NAME): $(OBJS)
	make -C libft
	$(CC) -o $(NAME) $(OBJS) -Llibft -lft -I $(INCLUDE)

all: $(NAME)

clean:
	$(RM) $(OBJS)
	make clean -C libft

fclean: clean
	${RM}  $(NAME)
	make fclean -C libft

re: fclean all

.PHONY: all clean fclean re