NAME = cub3d
MAP = map/map.cub
CC = clang
CFLAGS = -Wall -Wextra -Werror -O3 -ffast-math -g -std=c99
LIB = libft/libft.a
FT_PRINTF = ft_printf/ft_printf.a
MINILIBX = minilibx/libmlx.a

SRCDIR = sources
SRC = $(SRCDIR)/cub3d.c \
      $(SRCDIR)/free.c \
      $(SRCDIR)/parsing_0.c \
	  $(SRCDIR)/parsing_1.c \
      $(SRCDIR)/utils.c \
      $(SRCDIR)/rendering_0.c \
      $(SRCDIR)/rendering_1.c \
      $(SRCDIR)/check.c \
	  $(SRCDIR)/utils2.c \
	  $(SRCDIR)/movement.c \
	  $(SRCDIR)/floodfill.c

OBJ := $(SRC:.c=.o)

# Include and library paths for X11
INCLUDES = -I/opt/X11/include
LIBS := -L/opt/X11/lib -lX11 -lXext -lm -lz

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(OBJ) $(LIB) $(MINILIBX) $(FT_PRINTF)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(NAME) $(OBJ) $(FT_PRINTF) $(LIB) $(MINILIBX) $(LIBS)

$(LIB):
	$(MAKE) -C libft

$(MINILIBX):
	$(MAKE) -C minilibx

$(FT_PRINTF):
	$(MAKE) -C ft_printf

val:
	valgrind --read-var-info=yes --leak-check=full --show-leak-kinds=all --leak-check=full ./cub3d $(MAP) #to select the map run make val target MAP='map/yourmap'

clean:
	$(MAKE) clean -C libft
	$(MAKE) clean -C minilibx
	$(MAKE) clean -C ft_printf
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)
	$(MAKE) fclean -C libft
	$(MAKE) fclean -C ft_printf

re: fclean all

.PHONY: all clean fclean re
