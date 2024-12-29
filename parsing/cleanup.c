/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadou <dadou@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 01:25:41 by jealefev          #+#    #+#             */
/*   Updated: 2024/12/29 13:24:32 by dadou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void free_map(char **map)
{
    int i = 0;

    while (map[i])
    {
        free(map[i]);
        i++;
    }
    free(map);
}

void cleanup_and_exit(t_game *game, t_mlx *mlx, const char *error_msg)
{
    if (error_msg)
        fprintf(stderr, "Error: %s\n", error_msg);
    if (game && game->map)
        free_map(game->map);
    if (game)
        free(game);
    if (mlx->north_texture.img)
        mlx_destroy_image(mlx->mlx, mlx->north_texture.img);
    if (mlx->south_texture.img)
        mlx_destroy_image(mlx->mlx, mlx->south_texture.img);
    if (mlx->east_texture.img)
        mlx_destroy_image(mlx->mlx, mlx->east_texture.img);
    if (mlx->west_texture.img)
        mlx_destroy_image(mlx->mlx, mlx->west_texture.img);
    if (mlx->mlx_win)
        mlx_destroy_window(mlx->mlx, mlx->mlx_win);
    if (mlx->mlx)
        free(mlx->mlx);
    exit(1);
}

void clean_exit(t_game *game, t_mlx *mlx)
{
    if (game && game->map)
        free_map(game->map);
    if (game)
        free(game);
    if (mlx->north_texture.img)
        mlx_destroy_image(mlx->mlx, mlx->north_texture.img);
    if (mlx->south_texture.img)
        mlx_destroy_image(mlx->mlx, mlx->south_texture.img);
    if (mlx->east_texture.img)
        mlx_destroy_image(mlx->mlx, mlx->east_texture.img);
    if (mlx->west_texture.img)
        mlx_destroy_image(mlx->mlx, mlx->west_texture.img);
    if (mlx->mlx_win)
        mlx_destroy_window(mlx->mlx, mlx->mlx_win);
    if (mlx->mlx)
        free(mlx->mlx);
    exit(1);
}
