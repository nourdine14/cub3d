NAME = cub3d

SRC = main.c \
	  dda.c \
	  casting.c \
	  rays.c \
	  player.c

OBJ = ${SRC:.c=*.o}

INCS = cub3d.h

CC = gcc

CFLAGS = -Wall -Wextra -Werror

IMLX = -lmlx -framework OpenGL -framework AppKit

all: $(NAME)

$(NAME): $(OBJ)
		$(CC) -o $(NAME) ${CFLAGS} $(OBJ) $(IMLX)

%.o: %.c $(INCS)
	$(CC) -c $(CFLAGS) $<

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re