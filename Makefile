CC = cc
CFLAGS = -Wall -Wextra -Werror
MLXFLAGS = -lm -lX11 -lXext
MLXLIB = mlx/libmlx_Linux.a 
SRC = main.c \

OBJ = $(SRC:.c=.o)

NAME = cub3d

all: $(NAME)

$(MLXLIB):
	make -C mlx

$(NAME): $(OBJ) $(MLXLIB)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(MLXFLAGS) $(MLXLIB)

clean:
	rm -f $(OBJ)
	make -C mlx clean

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re 