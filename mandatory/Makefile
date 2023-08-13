NAME = cub3d

SRCS =	main.c \
		dda.c \
		casting.c \
		rays.c \
		player.c \
		check_wall.c \
		moves.c \
		parcing/parcing.c \
		parcing/delete_empty_lines.c \
		parcing/ft_atoi.c \
		parcing/ft_split.c \
		parcing/free.c \
		parcing/parcing_utils.c \
		parcing/check_directions.c \
		parcing/linked_lists_tools.c \
		get_next_line/get_next_line.c \
		get_next_line/get_next_line_utils.c \

OBJS = $(SRCS:.c=.o)

CFLAGS = -Wall -Werror -Wextra -g

MLXFLAGS = -lmlx -framework OpenGL -framework AppKit -fsanitize=address

HEADER = cub3d.h

RM = rm -rf

all: $(NAME) $(OBJS) $(HEADER)
	@printf "\033[0;32mDONE ✅"

%.o: %.c $(HEADER)
	@cc -c $(CFLAGS) $<  -o $@
	@printf "\033[0;32m{compiling : %-30s .....} \r" ${notdir $@} 

$(NAME): $(OBJS) $(HEADER)
	cc $(MLXFLAGS) -o $(NAME) $(OBJS)

clean:
	$(RM) $(OBJS)
	@printf "\033[0;32mDONE ✅"

fclean:clean
	$(RM) $(NAME)

re: fclean all

.SILENT : $(NAME) clean fclean re

.PHONY : all clean fclean re