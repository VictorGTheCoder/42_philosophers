SRCS	=	srcs/main.c srcs/philo_utils.c \
			srcs/philo_init.c srcs/philo_actions.c srcs/philo.c srcs/ft_atoi.c

OBJS	= ${SRCS:.c=.o}

CFLAGS	=  -Wall -Werror -Wextra
CC		= gcc

RM		= rm -f

NAME 	= philo

INCLUDE = includes

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o ${<:.c=.o}

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS) -I $(INCLUDE)
all: $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	${RM}  $(NAME)

re: fclean all

.PHONY: all clean fclean re