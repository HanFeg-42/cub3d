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
    char	*no_path;
    char	*so_path;
    char	*we_path;
    char	*ea_path;
    int		f_rgb;
    int		c_rgb;
} t_game_data;

#endif
