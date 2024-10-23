NAME = philo
CFLAGS = -Wextra -Wall -Werror -pthread

SRCS = get_set.c main.c monitor.c philo_action.c philo_tools.c start_eating.c tools.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

%.o: %.cc
	@cc $(CFLAGS) -o $@ -c $< && printf "Compiling: $(notdir $<)\n"

$(NAME): $(OBJS)
	@cc $(OBJS) -o $(NAME)

clean:
	@rm -rf $(OBJS)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re