/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadou <dadou@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 01:25:41 by jealefev          #+#    #+#             */
/*   Updated: 2024/12/29 12:50:56 by dadou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void flood_fill(char **map, int x, int y, t_game *game)
{
    if (x < 0 || x >= game->map_width || y < 0 || y >= game->map_height)
        return ;
    if (x >= (int)strlen(map[y]))
        return ;
    if (map[y][x] == '1' || map[y][x] == 'F')
        return ;
    map[y][x] = 'F';
    flood_fill(map, x + 1, y, game);
    flood_fill(map, x - 1, y, game);
    flood_fill(map, x, y + 1, game);
    flood_fill(map, x, y - 1, game);
}

void free_map_copy(char **map_copy, int height)
{
    int y = 0;
    while (y < height)
    {
        free(map_copy[y]); // Free each row
        y++;
    }
    free(map_copy); // Free main pointer
}

void check_map_copy(t_game *game, char **map_copy)
{
    int y;
    int x;

    y = 0;
    while (y < game->map_height)
    {
        x = 0;
        while (map_copy[y][x])
        {
            if (map_copy[y][x] == '0')
            {
                printf("Error: Map contains inaccessible areas at line %d, column %d\n",
                        y + 1, x + 1);
                free_map_copy(map_copy, game->map_height);
                clean_exit(game, game->mlx);
            }
            x++;
        }
        y++;
    }
}

void validate_accessible_map(t_game *game)
{
    int y;
    char **map_copy;

    map_copy = malloc(sizeof(char *) * (game->map_height + 1));
    if (!map_copy)
        check_malloc(game, game->mlx);

    y = 0;
    while (y < game->map_height)
    {
        map_copy[y] = ft_strdup(game->map[y]);
        if (!map_copy[y])
            check_malloc(game, game->mlx);
        y++;
    }
    map_copy[y] = NULL;
    flood_fill(map_copy, (int)game->posX, (int)game->posY, game);
    check_map_copy(game, map_copy);
    free_map_copy(map_copy, game->map_height);
}


