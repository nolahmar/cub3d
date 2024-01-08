NAME 			= cub3D
MINILIBX_PATH   = ./miniLibX
SRCS 			= init_wind.c main.c key_hok.c ray_cast.c
OBJS			= ${SRCS:.c=.o}
INCLUDE 		= cube3d.h
LIBFT 			= libft
MINILIBX 		= miniLibX
CC				= gcc -g -Wall -Wextra -Werror #-fsanitize=address
RM				= rm -f
MLXFLAGS 		= -I ./miniLibX -L ./miniLibX -lmlx -framework OpenGl -framework Appkit
# -I Add the directory dir to the list of directories to be searched for header files
# -L Searches the library when linking

all:			 ${NAME}
$(NAME):		${OBJS} 
				@$(CC) $(MLXFLAGS) $(LIBFLAGS) -I./ $(OBJS) -o $@ 
clean:			clean
				@${RM} ${OBJS}
fclean:			clean
				@${RM} ${NAME}
re:				fclean all

# make other makefiles compile with the -C flag
# The -C flag makes you go to the appropriate path and do the asked command
				
.PHONY: all fclean clean re