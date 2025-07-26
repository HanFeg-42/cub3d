#ifndef CUB3D_H
# define CUB3D_H

# include "libft/libft.h"
# include "minilibx-linux/mlx.h"
# include <X11/keysym.h>
# include <stdbool.h>

# define WINDOW_WIDTH 800
# define WINDOW_HEIGHT 600

typedef struct s_game_data
{
    void	*mlx_ptr;
    void	*win_ptr;
    char	*map_path;
    char	**map;
    int		fd;
    char	*NO_path;
    char	*SO_path;
    char	*WE_path;
    char	*EA_path;
    int		F_RGB;
    int		C_RGB;
} t_game_data;

#endif
