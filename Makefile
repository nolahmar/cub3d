NAME = Cub3d
LIBFT = libft/libft.a
MINILIBX = mlx/libmlx.a

SRC =  ./parsing/color_texture.c \
		./parsing/map.c \
		./parsing/parse_cub.c \
		./parsing/parse.c \
		./parsing/text_col_err.c \
		./parsing/text_col_utils.c \
		./parsing/texture_color.c \
		./parsing/utils.c \
		./parsing/utils2.c \
		./src/main.c \
		./src/draw_3d.c \
		./src/horizontal_vertical_ray_cast.c \
		./src/key_hok.c \
		./src/ray_cast.c \
		./src/textur_mapping.c \
		./src/corr_ray.c \
		./src/init.c \
		./src/free.c

CC = cc
CFLAGS = -Wall -Wextra -Werror # -fsanitize=address
MLX = -Lmlx -lmlx -framework OpenGL -framework Appkit
OBJ = $(SRC:.c=.o)

all : ${NAME}

$(NAME) : $(OBJ) $(LIBFT) $(MINILIBX)
	$(CC) $(CFLAGS) $(MLX) $(SRC) $(LIBFT) -o $(NAME)

$(MINILIBX):
	$(MAKE) -C mlx

$(LIBFT):
	$(MAKE) -C libft

clean:
	$(MAKE) -C mlx clean
	rm -f $(OBJ) 

fclean: clean
	rm -f $(NAME)

re : fclean all