#include "cub3d.h"

void	load_one_texture(t_game *game, t_img *texture, char *path)
{
	texture->img = mlx_xpm_file_to_image(game->mlx, path,
			&texture->width, &texture->height);
	if (texture->img == NULL)
	{
		printf("Error\nFailed to load texture: %s\n", path);
		exit_game(game, "Texture loading failed.", EXIT_FAILURE);
	}
	texture->addr = mlx_get_data_addr(texture->img, &texture->bits_per_pixel,
			&texture->line_length, &texture->endian);
	if (texture->addr == NULL)
	{
		printf("Error\nFailed to get data addr for: %s\n", path);
		exit_game(game, "mlx_get_data_addr failed.", EXIT_FAILURE);
	}
}

void init_wall_textures(t_game *game)
{
    load_one_texture(game, &game->texture[NORTH], game->config.no);
	load_one_texture(game, &game->texture[SOUTH], game->config.so);
	load_one_texture(game, &game->texture[EAST], game->config.ea);
	load_one_texture(game, &game->texture[WEST], game->config.we);
}

void init_anim_textures(t_game *game)
{
    int i;
    char *path;

    i = 0;
    load_one_texture(game,&game->gun.idle,"textures/idle/idle.xpm");
    while (i < NUM_FRAME_SHOT)
    {
        path= gc_str_join("textures/shot/shot",gc_itoa(i+1));
        path= gc_str_join(path,".xpm");
        load_one_texture(game, &game->gun.shot[i], path);
        i++;
    }
    i = 0;
    while(i < NUM_FRAME_MOVE)
    {
        path= gc_str_join("textures/move/walk",gc_itoa(i+1));
        path= gc_str_join(path,".xpm");
        load_one_texture(game, &game->gun.move[i], path);
        i++;
    }
    game->gun.current_frame = 0;
    game->gun.anim_timer = 0; 
}
