NAME = cub3d

OUTPUT_PATH = .

all:
	@make -C mandatory
	@cp mandatory/$(NAME) $(OUTPUT_PATH)

bonus:
	make -C bonus
	cp bonus/$(NAME) $(OUTPUT_PATH)

clean:
	make clean -C bonus
	make clean -C mandatory

fclean:
	make fclean -C bonus
	make fclean -C mandatory
	rm -f $(NAME)

re: fclean all

.SILENT : $(NAME) clean fclean re bonus

.PHONY : all clean fclean re bonus