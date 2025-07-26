#include "includes/cub3D.h"

// TODO: parse_arguments
// TODO: initialize_game_data

int main(int ac, char **av)
{
    t_game_data data;
    // Initialize the game data structure
    data.mlx_ptr = NULL;
    data.win_ptr = NULL;
    data.map_path = NULL;
    data.map = NULL;
    if (!parse_args(ac, av, &data))
        return (1);

    // Example usage of the argument
    printf("Argument provided: %s\n", av[1]);

    // Here you can add more functionality as needed
    return 0;
}
