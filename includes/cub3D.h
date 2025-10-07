/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 23:40:45 by kali              #+#    #+#             */
/*   Updated: 2025/10/06 20:34:33 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include <X11/keysym.h>
# include <stdbool.h>

# define WINDOW_WIDTH 800
# define WINDOW_HEIGHT 600
# define SCALE 50

# define BUFFER_SIZE 32
# define NX 0
# define NY -1
# define SX 0
# define SY 1
# define EX 1
# define EY 0
# define WX -1
# define WY 0

typedef struct s_game_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	char	*map_path;
	char	*join;
	char	**map; // 2D array of strings representing the map
	int		fd;
	char	*no_path;
	char	*so_path;
	char	*we_path;
	char	*ea_path;
	int		f_rgb;
	int		c_rgb;
}			t_game_data;

bool	parse_args(int ac, char **av, t_game_data *data);
char	*get_next_line(int fd, int f);
void	init_map_matrix(t_game_data *data);
void	map_line_loader(char *line, t_game_data *data);
void	load_line(char *line, t_game_data *data);
void	clean_and_exit(char *message);
int		is_numeric(const char *a);
bool	conf_params_loaded(t_game_data *data);
void	ft_free_split(char **arr);

#endif
