NAME = Cub3d

SRC = main.c init_wind.c key_hok.c ray_cast.c 

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
