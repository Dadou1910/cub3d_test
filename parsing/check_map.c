/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadou <dadou@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 01:25:41 by jealefev          #+#    #+#             */
/*   Updated: 2024/12/29 12:51:23 by dadou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"



int    help_walls_count(t_game *game, int x, int y)
{
    int count;

    // Only check for '1's at the edges
    if (game->map[y][x] == '1' && (y == 0 || x == 0 || y == game->map_height - 1 || x == game->map_width - 1))
    {
        count = 0;

        // Check all 8 directions
        if (y > 0 && game->map[y - 1][x] == '1') count++;             // Up
        if (y < game->map_height - 1 && game->map[y + 1][x] == '1') count++; // Down
        if (x > 0 && game->map[y][x - 1] == '1') count++;             // Left
        if (x < game->map_width - 1 && game->map[y][x + 1] == '1') count++; // Right

        if (y > 0 && x > 0 && game->map[y - 1][x - 1] == '1') count++;     // Top-Left
        if (y > 0 && x < game->map_width - 1 && game->map[y - 1][x + 1] == '1') count++; // Top-Right
        if (y < game->map_height - 1 && x > 0 && game->map[y + 1][x - 1] == '1') count++; // Bottom-Left
        if (y < game->map_height - 1 && x < game->map_width - 1 && game->map[y + 1][x + 1] == '1') count++; // Bottom-Right

        return (count >= 2); // Return 1 if at least 2 neighbors are '1'
    }

    return (1); // Return valid for non-edge '1's
}


// Check if the map is surrounded by walls
int is_surrounded_by_walls(t_game *game)
{
    int y;
    int x;
    
    y = 0;
    while (y < game->map_height)
    {
        x = 0;
        while (x < game->map_width)
        {
            if (!help_walls(game, x, y))
                return (0);
            if (!help_walls_count(game, x, y))
                return (0);
            x++;
        }
        y++;
    }
    return (1);
}

void    helper_val_map(t_game *game, int *player_count, int x, int y)
{
    (*player_count)++;
    game->posX = x + 0.5;
    game->posY = y + 0.5;
    game->map[y][x] = '0';
}

void    check_val_map(t_game *game, int player_count)
{
    if (player_count != 1)
    {
        if (player_count == 0)
            cleanup_and_exit(game, game->mlx, "No player position");
        else
            cleanup_and_exit(game, game->mlx, "Multiple player positions");
    }
    if (!is_surrounded_by_walls(game))
        cleanup_and_exit(game, game->mlx, "Map is not properly surrounded by walls");
}

void validate_map(t_game *game)
{
    int y;
    int x;
    int player_count;

    x = 0;
    y = 0;
    player_count = 0;
    while (y < game->map_height)
    {
        x = 0;
        while (game->map[y][x])
        {
            if (!is_valid_map_char(game->map[y][x]))
                cleanup_and_exit(game, game->mlx, "Invalid map char");
            if (game->map[y][x] == 'P')
                helper_val_map(game, &player_count, x, y);
            x++;
        }
        y++;
    }
    check_val_map(game, player_count);
}


