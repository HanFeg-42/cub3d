NAME	=	cub3D
CC	=	cc
CFLAGS	=	-Wall -Wextra -Werror
MLXFLAGS	=	-lXext -lX11
HEADER  =       so_long.h
LIBMLX  =       minilibx-linux/libmlx_Linux.a
LMLX    =       minilibx-linux/libmlx.a
LIBFT_D =       ./libft
LIBFT   =       libft/libft.a
PRINTF_D=       ./ft_printf
PRINTF  =       ft_printf/ft_printf.a
CLEAN   =       clean
FCLEAN  =       fclean
OBJ             =       ${SRC:.c=.o}
OBJ_B   =       ${SRC_B:.c=.o}

