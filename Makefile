NAME = pipex

CC = cc

CFLAGS = -Wall -Werror -Wextra -g

SRCS =  pipex_split.c pipex.c pipex_utils.c

LIBFT_PATH = libft


LIBFT = $(LIBFT_PATH)/libft.a

OBJS = ${SRCS:.c=.o}

all: $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(OBJS) $(LIBFT) -o $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_PATH)

clean:
	@rm -f $(OBJS)
	@$(MAKE) clean -C $(LIBFT_PATH)

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) fclean -C $(LIBFT_PATH)

re: fclean all
	clear

.PHONY: all clean fclean re