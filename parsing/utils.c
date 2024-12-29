/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadou <dadou@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 01:25:41 by jealefev          #+#    #+#             */
/*   Updated: 2024/12/29 12:51:27 by dadou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void    check_malloc(t_game *game, t_mlx *mlx)
{
    cleanup_and_exit(game, mlx, "Failed malloc");
}

t_texture *select_texture(t_game *game, t_mlx *mlx, int side)
{
    if (side == 0)
        return (game->ray.rayDirX > 0) ? &mlx->east_texture : &mlx->west_texture;
    return (game->ray.rayDirY > 0) ? &mlx->south_texture : &mlx->north_texture;
}

void draw_tile(t_mlx *mlx, int x, int y, int color)
{
    int i = 0;
    while (i < TILE_SIZE_MINI)
    {
        int j = 0;
        while (j < TILE_SIZE_MINI)
        {
            my_mlx_pixel_put(mlx, x + i, y + j, color);
            j++;
        }
        i++;
    }
}

int is_valid_map_char(char c)
{
    if (c == '0' || c == '1' || c == ' ' || c == 'P')
        return (1); // Allowed characters
    return (0);
}

int    help_walls(t_game *game, int x, int y)
{
    if (game->map[y][x] == '0' || game->map[y][x] == 'P')
    {
        if (y == 0 || x == 0 || y == game->map_height - 1 || x == game->map_width - 1)
            return (0);
        if (game->map[y - 1][x] == ' ' || game->map[y - 1][x] == '\0' ||
            game->map[y + 1][x] == ' ' || game->map[y + 1][x] == '\0' ||
            game->map[y][x - 1] == ' ' || game->map[y][x - 1] == '\0' ||
            game->map[y][x + 1] == ' ' || game->map[y][x + 1] == '\0')
            return (0);
    }
    return(1);
}
