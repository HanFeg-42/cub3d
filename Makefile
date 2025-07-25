NAME		=	cub3D
CC		=	cc
RM		=	rm -f
CFLAGS		=	-Wall -Wextra -Werror
MLXFLAGS	=	-lXext -lX11
HEADER		=	cub3D.h
LIBMLX_D	=       ./minilibx-linux
LIBMLX_LINUX	=       minilibx-linux/libmlx_Linux.a
LIBMLX		=       minilibx-linux/libmlx.a
LIBFT_D		=       ./libft
LIBFT		=       libft/libft.a
CLEAN		=       clean
FCLEAN		=       fclean
SRC		=       main.c
OBJ		=       ${SRC:%.c=$(OBJ_D)/%.o}
OBJ_D		=	obj

$(OBJ_D)/%.o:%.c
	mkdir -p $(OBJ_D)
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	$(MAKE) -s -C $(LIBFT_D)
	$(MAKE) -s -C $(LIBMLX_D)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(LIBMLX) $(LIBMLX_LINUX) $(MLXFLAGS) -o $(NAME)
	@echo "compiled successfully"

bonus: all

clean:
	$(MAKE) $(CLEAN) -s -C $(LIBFT_D)
	$(MAKE) $(CLEAN) -s -C $(LIBMLX_D)
	$(RM) -r $(OBJ_D)

fclean: clean
	$(MAKE) $(FCLEAN) -s -C $(LIBFT_D)
	$(RM) $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re
.SECONDARY:
