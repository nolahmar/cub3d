NAME = Cub3d

SRC = main.c  key_hok.c ray_cast.c horizontal_vertical_ray_cast.c draw_3d.c textur_mapping.c

CC = cc

CFLAGS = -Wall -Wextra -Werror -fsanitize=address

OBJ = $(SRC:.c=.o)

MLX = -lmlx -framework OpenGL -framework Appkit

all : ${NAME}

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(MLX) $(SRC) -o $(NAME)

clean:
	rm -f $(OBJ) 

fclean: clean
	rm -f $(NAME)

re : fclean all
