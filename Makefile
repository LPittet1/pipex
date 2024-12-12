NAME = pipex

CC = cc

CFLAGS = -Wall -Werror -Wextra -g

SRCDIR = srcs/

SRCS =  srcs/pipex_split.c srcs/pipex.c srcs/pipex_utils.c \
		srcs/parsing.c srcs/tries1.c srcs/tries2.c

BONUSDIR = bonus/

SRCS_BONUS = $(BONUSDIR)pipex_split.c $(BONUSDIR)pipex_bonus.c \
		$(BONUSDIR)pipex_utils.c $(BONUSDIR)parsing.c  $(BONUSDIR)heredoc.c \
		$(BONUSDIR)tries1.c $(BONUSDIR)tries2.c

LIBFT_PATH = libft

LIBFT = $(LIBFT_PATH)/libft.a

OBJS = ${SRCS:.c=.o}

OBJS_BONUS = ${SRCS_BONUS:.c=.o}

all: $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_PATH)

clean:
	@rm -f $(OBJS) $(OBJS_BONUS)
	@$(MAKE) clean -C $(LIBFT_PATH)

fclean: clean
	@rm -f $(NAME) $(NAME_BONUS)
	@$(MAKE) fclean -C $(LIBFT_PATH)

bonus: $(OBJS_BONUS) $(LIBFT)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS_BONUS) $(LIBFT)

re: fclean all

.PHONY: all clean fclean re