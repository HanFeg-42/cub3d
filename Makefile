NAME		=	cub3D
CC			=	cc
RM			=	rm -f
CFLAGS		=	-Wall -Wextra -Werror -g3 -MMD -MP -I$(INC_D) #-fsanitize=address
MLXFLAGS	=	-lXext -lX11 -lm
LIBMLX_D	=	minilibx-linux
LIBMLX_LINUX	=	$(LIBMLX_D)/libmlx_Linux.a
LIBFT_D		=	libft
INC_D		=	includes
LIBFT		=	$(LIBFT_D)/libft.a
OBJ_D		=	obj
OBJ_D_B		=	obj_bonus

SRC			=	$(shell find src/ -name "*.c")
SRC_B		=	$(shell find src_bonus/ -name "*.c")
OBJ			=	$(SRC:%.c=$(OBJ_D)/%.o)
OBJ_B		=	$(SRC_B:%.c=$(OBJ_D_B)/%.o)
DEP			=	$(OBJ:.o=.d)
DEP_B		=	$(OBJ_B:.o=.d)

$(OBJ_D)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_D_B)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	@$(MAKE) -s -C $(LIBFT_D)
	@$(MAKE) -s -C $(LIBMLX_D)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(LIBMLX_LINUX) $(MLXFLAGS) -o $(NAME)
	@echo "✅ Mandatory compiled successfully!"

bonus: $(NAME) $(OBJ_B)
	@$(MAKE) -s -C $(LIBFT_D)
	@$(MAKE) -s -C $(LIBMLX_D)
	$(CC) $(CFLAGS) $(OBJ_B) $(LIBFT) $(LIBMLX_LINUX) $(MLXFLAGS) -o $(NAME)
	@echo "✅ Bonus compiled successfully!"

clean:
	@$(MAKE) clean -s -C $(LIBFT_D)
	@$(MAKE) clean -s -C $(LIBMLX_D)
	@$(RM) -r $(OBJ_D) $(OBJ_D_B)

fclean: clean
	@$(MAKE) fclean -s -C $(LIBFT_D)
	@$(RM) $(NAME)

re: fclean
	@$(MAKE) all -s

.PHONY: all bonus clean fclean re
-include $(DEP) $(DEP_B)
.SECONDARY: