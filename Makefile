NAME = pipex

SRC =	main.c \
			pipex.c \
      error_utils.c \
			second_utils.c \
      ft_split.c \
			ft_strjoin.c \
      ft_printf/ft_print_ptr.c ft_printf/ft_printf.c ft_printf/ft_put_unsigned.c \
      ft_printf/ft_putchar.c ft_printf/ft_puthex.c ft_printf/ft_putnbr.c ft_printf/ft_putstr.c

OBJ = $(SRC:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)
	@echo "✅ Compilation terminée pour PIPEX !"

clean:
	rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)
	@echo "🧹 Nettoyage complet terminé."

re: fclean all

.PHONY: all clean fclean re
