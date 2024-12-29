/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadou <dadou@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 01:25:41 by jealefev          #+#    #+#             */
/*   Updated: 2024/12/29 13:26:05 by dadou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void draw_player(t_game *game, t_mlx *mlx, t_minmap minmap)
{
    int player_screen_x = (game->posX - minmap.start_x) * TILE_SIZE_MINI;
    int player_screen_y = (game->posY - minmap.start_y) * TILE_SIZE_MINI;

    int i = -PLAYER_SIZE;
    while (i <= PLAYER_SIZE)
    {
        int j = -PLAYER_SIZE;
        while (j <= PLAYER_SIZE)
        {
            int px = player_screen_x + i;
            int py = player_screen_y + j;
            if (px >= 0 && px < MINIMAP_SIZE && py >= 0 && py < MINIMAP_SIZE)
                my_mlx_pixel_put(mlx, px, py, 0xD98085);
            j++;
        }
        i++;
    }
}

void draw_direction_line(t_game *game, t_mlx *mlx, t_minmap minmap)
{
    int player_screen_x = (game->posX - minmap.start_x) * TILE_SIZE_MINI;
    int player_screen_y = (game->posY - minmap.start_y) * TILE_SIZE_MINI;

    int line_length = 14;
    int i = 0;
    while (i < line_length)
    {
        int line_x = player_screen_x + (int)(game->dirX * i);
        int line_y = player_screen_y + (int)(game->dirY * i);
        if (line_x >= 0 && line_x < MINIMAP_SIZE && line_y >= 0 && line_y < MINIMAP_SIZE)
            my_mlx_pixel_put(mlx, line_x, line_y, 0xD98085);
        i++;
    }
}

void render_minimap_viewport(t_game *game, t_mlx *mlx, t_minmap minmap)
{
    int y;
    
    y = minmap.start_y;
    while (y < minmap.end_y)
    {
        int x = minmap.start_x;
        while (x < minmap.end_x)
        {
            int color = 0xE6E6FA;
            if (game->map[y][x] == '1')
                color = 0xFFD1DC;
            else if (game->map[y][x] == '0')
                color = 0xFFB6C1;

            int screen_x = (x - minmap.start_x) * TILE_SIZE_MINI;
            int screen_y = (y - minmap.start_y) * TILE_SIZE_MINI;
            draw_tile(mlx, screen_x, screen_y, color);
            x++;
        }
        y++;
    }
}

void    helper_minimap(int game_param, int *end, int *start)
{
    if (*end > game_param)
    {
        *start = game_param - MINIMAP_SIZE / TILE_SIZE_MINI;
        *end = game_param;
    }
}

void render_minimap(t_game *game, t_mlx *mlx)
{
    t_minmap minmap;
    minmap = minmap;
    init_minmap(game);
    minmap.start_x = (int)game->posX - MINIMAP_SIZE / (2 * TILE_SIZE_MINI);
    minmap.start_y = (int)game->posY - MINIMAP_SIZE / (2 * TILE_SIZE_MINI);
    if (minmap.start_x < 0)
        minmap.start_x = 0;
    if (minmap.start_y < 0)
        minmap.start_y = 0;
    minmap.end_x = minmap.start_x + MINIMAP_SIZE / TILE_SIZE_MINI;
    minmap.end_y = minmap.start_y + MINIMAP_SIZE / TILE_SIZE_MINI;
    helper_minimap(game->map_width, &minmap.end_x, &minmap.start_x);
    helper_minimap(game->map_height, &minmap.end_y, &minmap.start_y);
    if (minmap.start_x < 0)
        minmap.start_x = 0;
    if (minmap.start_y < 0)
        minmap.start_y = 0;
    render_minimap_viewport(game, mlx, minmap);
    draw_player(game, mlx, minmap);
    draw_direction_line(game, mlx, minmap);
}
