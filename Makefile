src_files = functions/ft_strlen.c functions/ft_strnstr.c functions/get_next_line.c functions/get_next_line_utils.c main.c

objects = $(src_files:.c=.o)

NAME = ALLOCATER

clean: 
	rm $(objects)

run : $(objects)
	gcc $(objects) -fsanitize=address -g -o $(NAME) && rm $(objects) && ./$(NAME)

