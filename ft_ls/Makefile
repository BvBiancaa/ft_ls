NAME=ft_ls

SRCS=main.c env_parse.c read_dir.c utils.c parse_flag.c window_size.c file_type.c colors.c

all: $(NAME)

$(NAME):
	make -C Libft
	@gcc -g -Wall -Wextra -Werror -o $(NAME) $(SRCS) -L./Libft -lft

clean:
	make -C Libft clean
	@make -C libft clean

fclean:
	make -C Libft fclean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re