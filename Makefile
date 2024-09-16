CC = cc
CFLAGS = -Wall -Wextra -Werror -I.
LIBFLAGS = -L./libft/ -lft
MLXFLAGS = -Lmlx -lmlx -lm -lX11 -lXext -lXrandr -lXi
MLXLIB = mlx/libmlx_Linux.a 

SRC = main.c \
	src/my_pixel_put.c \
	src/parsing/parsing.c \
	src/exec/ft_mlx_event.c \
	src/exec/utils.c \

OBJ = $(SRC:.c=.o)

LIBFT_PATH = ./libft/
LIBFT = $(LIBFT_PATH)libft.a


NAME = cub3D

all: $(NAME)

$(MLXLIB):
	make -C mlx

$(NAME): $(OBJ) $(MLXLIB) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(MLXFLAGS) $(MLXLIB) $(LIBFLAGS)

$(LIBFT):
	$(MAKE) -C $(LIBFT_PATH) all bonus

clean:
	rm -f $(OBJ)
	make -C mlx clean
	make -C $(LIBFT_PATH) fclean

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re 