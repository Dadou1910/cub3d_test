/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadou <dadou@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 01:25:41 by jealefev          #+#    #+#             */
/*   Updated: 2024/12/29 13:20:44 by dadou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void init_ray(t_ray ray)
{
    ray.rayDirX = 0.0;
    ray.rayDirY = 0.0;
    ray.deltaDistX = 0.0;
    ray.deltaDistY = 0.0;
    ray.sideDistX = 0.0;
    ray.sideDistY = 0.0;
    ray.cameraX = 0.0;
    ray.stepX = 0;
    ray.stepY = 0;
}

void    init_count(t_game *game)
{
    game->count[0] = 0;
    game->count[1] = 0;
    game->count[2] = 0;
    game->count[3] = 0;
    game->count[4] = 0;
    game->count[5] = 0;
}

void    init_minmap(t_game *game)
{
    game->minmap.start_x = 0;
    game->minmap.start_y = 0;
    game->minmap.end_x = 0;
    game->minmap.end_y = 0;
}

void init_game(t_game *game, t_mlx *mlx)
{
    game->angle = 0.0;
    game->posX = 0;
    game->posY = 0;
    game->dirX = cos(game->angle);
    game->dirY = sin(game->angle);
    game->planeX = -sin(game->angle) * FOV;
    game->planeY = cos(game->angle) * FOV;
    game->time = 0.0;
    game->oldTime = 0.0;
    game->frameTime = 0.0;
    game->currentStripe = 0;
    init_ray(game->ray);
    game->ray.mapX = (int)game->posX;
    game->ray.mapY = (int)game->posY;
    game->map_width = 0;
    game->map_height = 0;
    init_count(game);
    game->keys.a = 0;
    game->keys.s = 0;
    game->keys.w = 0;
    game->keys.d = 0;
    game->init = 0;
    game->mlx = mlx;
    game->map = NULL;
}

void init_mlx(t_mlx *mlx)
{
    mlx->mlx = mlx_init();
    mlx->mlx_win = mlx_new_window(mlx->mlx, WIDTH, HEIGHT, "Cub3D");
    mlx->img = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
    mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel,
                &mlx->line_length, &mlx->endian);
    mlx->flower_texture.img = mlx_xpm_file_to_image(mlx->mlx, "exec/flower.xpm",
                            &mlx->flower_texture.width, &mlx->flower_texture.height);
    if (!mlx->flower_texture.img)
    {
        printf("Error: Failed to get flower img.\n");
        exit(1);
    }
    mlx->flower_texture.addr = mlx_get_data_addr(mlx->flower_texture.img,
                            &mlx->flower_texture.bpp, &mlx->flower_texture.line_len,
                            &mlx->flower_texture.endian);
    if (!mlx->flower_texture.addr)
    {
        printf("Error: Failed to get flower texture data address.\n");
        exit(1);
    }
}
