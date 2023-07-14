# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nakebli <nakebli@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/10 12:11:21 by nakebli           #+#    #+#              #
#    Updated: 2023/07/11 13:27:04 by nakebli          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =    cub3D

SRCS =	main.c \
	parcing/parcing.c \
	parcing/parcing_utils.c \
	parcing/linked_lists_tools.c \
	get_next_line/get_next_line.c \
	get_next_line/get_next_line_utils.c \

OBJS = $(SRCS:.c=.o)

CFLAGS = -Wall -Werror -Wextra

MLXFLAGS = -lmlx -framework OpenGL -framework AppKit

HEADER = cub.h

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