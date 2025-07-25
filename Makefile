NAME		=	cub3D
CC		=	cc
CFLAGS		=	-Wall -Wextra -Werror
MLXFLAGS	=	-lXext -lX11
HEADER  	=       
LIBMLX_D	=       ./minilibx-linux
LIBMLX_LINUX	=       minilibx-linux/libmlx_Linux.a
LIBMLX		=       minilibx-linux/libmlx.a
LIBFT_D		=       ./libft
LIBFT		=       libft/libft.a
CLEAN		=       clean
FCLEAN		=       fclean
OBJ		=       ${SRC:.c=.o}
OBJ_B		=       ${SRC_B:.c=.o}

