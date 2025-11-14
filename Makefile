NAME		=	cub3D
CC		=	cc
RM		=	rm -f
CFLAGS		=	-Wall -Wextra -Werror -g3 -MMD -MP -I$(INC_D) -fsanitize=address
MLXFLAGS	=	-lXext -lX11 -lm
LIBMLX_D	=	minilibx-linux
LIBMLX_LINUX	=	$(LIBMLX_D)/libmlx_Linux.a
LIBFT_D		=	libft
INC_D		=	includes
LIBFT		=	$(LIBFT_D)/libft.a
OBJ_D		=	obj

SRC		=	$(shell find src/ -name "*.c")
OBJ		=	$(SRC:%.c=$(OBJ_D)/%.o)
DEP		=	$(OBJ:.o=.d)

$(OBJ_D)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	@$(MAKE) -s -C $(LIBFT_D)
	@$(MAKE) -s -C $(LIBMLX_D)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(LIBMLX_LINUX) $(MLXFLAGS) -o $(NAME)
	@echo "✅ Compiled successfully!"

bonus: all

clean:
	@$(MAKE) clean -s -C $(LIBFT_D)
	@$(MAKE) clean -s -C $(LIBMLX_D)
	@$(RM) -r $(OBJ_D)

fclean: clean
	@$(MAKE) fclean -s -C $(LIBFT_D)
	@$(RM) $(NAME)

re: fclean
	@$(MAKE) all -s

.PHONY: all bonus clean fclean re
-include $(DEP)
#.SECONDARY:
