NAME = philo
CC = gcc
CFLAGS = -Wall -Wextra -Werror -pthread -g
SRCS = main.c create.c init.c monitor.c philo_utils.c philo_utils2.c routine.c

.SECONDARY: $(OBJS)
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

%.o: %.c philosopher.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
