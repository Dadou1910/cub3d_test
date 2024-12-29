/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadou <dadou@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 01:25:41 by jealefev          #+#    #+#             */
/*   Updated: 2024/12/29 12:55:14 by dadou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"



void check_duplicate_or_missing(t_game *game, t_mlx *mlx)
{
    if (game->count[0] > 1 || game->count[0] == 0)
        cleanup_and_exit(game, mlx, "Error: Duplicate or missing 'NO' texture");
    if (game->count[1] > 1 || game->count[1] == 0)
        cleanup_and_exit(game, mlx, "Error: Duplicate or missing 'SO' texture");
    if (game->count[2] > 1 || game->count[2] == 0)
        cleanup_and_exit(game, mlx, "Error: Duplicate or missing 'WE' texture");
    if (game->count[3] > 1 || game->count[3] == 0)
        cleanup_and_exit(game, mlx, "Error: Duplicate or missing 'EA' texture");
    if (game->count[4] > 1 || game->count[4] == 0)
        cleanup_and_exit(game, mlx, "Error: Duplicate or missing floor color");
    if (game->count[5] > 1 || game->count[5] == 0)
        cleanup_and_exit(game, mlx, "Error: Duplicate or missing ceiling color");
}

void validate_config_map(char *line, t_game *game, t_mlx *mlx)
{
        if (strncmp(line, "NO ", 3) == 0)
            game->count[0]++;
        else if (strncmp(line, "SO ", 3) == 0)
            game->count[1]++;
        else if (strncmp(line, "WE ", 3) == 0)
            game->count[2]++;
        else if (strncmp(line, "EA ", 3) == 0)
            game->count[3]++;
        else if (strncmp(line, "F ", 2) == 0)
            game->count[4]++;
        else if (strncmp(line, "C ", 2) == 0)
            game->count[5]++;
}

void parse_config(char *line, t_mlx *mlx, t_game *game)
{
    char *trimmed;

    trimmed = trim_whitespace(line);
    validate_config_map(trimmed, game, mlx);
    if (strncmp(trimmed, "NO ", 3) == 0)
        load_texture(mlx, &mlx->north_texture, game, trimmed + 3);
    else if (strncmp(trimmed, "SO ", 3) == 0)
        load_texture(mlx, &mlx->south_texture, game, trimmed + 3);
    else if (strncmp(trimmed, "WE ", 3) == 0)
        load_texture(mlx, &mlx->west_texture, game, trimmed + 3);
    else if (strncmp(trimmed, "EA ", 3) == 0)
        load_texture(mlx, &mlx->east_texture, game, trimmed + 3);
    else if (strncmp(trimmed, "F ", 2) == 0)
        mlx->floor_color = parse_color(game, trimmed + 2);
    else if (strncmp(trimmed, "C ", 2) == 0)
        mlx->ceiling_color = parse_color(game, trimmed + 2);
}

int is_valid_color(int color, const char *type)
{
    if (color < 0x000000 || color > 0xFFFFFF)
        return (0);
    return (1);
}

void validate_config(t_mlx *mlx)
{
    if (!is_valid_color(mlx->floor_color, "floor"))
        cleanup_and_exit(NULL, mlx, "Invalid floor color");
    if (!is_valid_color(mlx->ceiling_color, "ceiling"))
        cleanup_and_exit(NULL, mlx, "Invalid ceiling color");
}

