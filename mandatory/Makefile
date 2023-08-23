NAME = cub3d

SRCS =	main.c \
		get_next_line/get_next_line_utils.c \
		get_next_line/get_next_line.c \
		cast_draw/horizontal_vertical.c \
		cast_draw/draw_walls.c \
		cast_draw/check_wall.c \
		cast_draw/casting.c \
		cast_draw/rays.c \
		parcing/delete_empty_lines.c \
		parcing/linked_lists_tools.c \
		parcing/check_directions.c \
		parcing/parcing_utils.c \
		parcing/rgb_parce.c \
		parcing/ft_split.c \
		parcing/parcing.c \
		parcing/ft_atoi.c \
		parcing/free.c \
		moves/move_player.c \
		moves/key_handle.c \
		moves/player.c \
		moves/moves.c \
		moves/doors.c \
		dda.c \

OBJS = $(SRCS:.c=.o)

CFLAGS = -Wall -Werror -Wextra

MLXFLAGS = -lmlx -framework OpenGL -framework AppKit

HEADER = cub3d.h

RM = rm -rf

all: $(NAME) $(OBJS)
	@printf "\033[0;32mDONE ✅"

%.o: %.c $(HEADER)
	@cc -c $(CFLAGS) $<  -o $@
	@printf "\033[0;32m{compiling : %-30s .....} \r" ${notdir $@} 

$(NAME): $(OBJS)
	cc $(MLXFLAGS) $(CFLAGS) -o $(NAME) $(OBJS)

clean:
	$(RM) $(OBJS)
	@printf "\033[0;32mDONE ✅"

fclean:clean
	$(RM) $(NAME)

re: fclean all

.SILENT : $(NAME) clean fclean re

.PHONY : all clean fclean re