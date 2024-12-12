NAME = pipex

NAME_BONUS = pipex_bonus

CC = cc

CFLAGS = -Wall -Werror -Wextra -g

SRCS =  pipex_split.c pipex.c pipex_utils.c parsing.c tries1.c tries2.c

SRCS_BONUS = pipex_split.c pipex_bonus.c pipex_utils.c parsing.c  heredoc.c tries1.c tries2.c

LIBFT_PATH = libft

LIBFT = $(LIBFT_PATH)/libft.a

OBJS = ${SRCS:.c=.o}

OBJS_BONUS = ${SRCS_BONUS:.c=.o}

all: $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(OBJS) $(LIBFT) -o $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_PATH)

clean:
	@rm -f $(OBJS) $(OBJS_BONUS)
	@$(MAKE) clean -C $(LIBFT_PATH)

fclean: clean
	@rm -f $(NAME) $(NAME_BONUS)
	@$(MAKE) fclean -C $(LIBFT_PATH)

bonus: $(NAME_BONUS)

$(NAME_BONUS): $(OBJS_BONUS) $(LIBFT)
	@$(CC) $(OBJS_BONUS) $(LIBFT) -o $(NAME_BONUS)

re: fclean all
	clear

.PHONY: all clean fclean re