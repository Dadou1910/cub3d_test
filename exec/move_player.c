/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadou <dadou@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 01:25:41 by jealefev          #+#    #+#             */
/*   Updated: 2024/12/29 11:44:07 by dadou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void    update_time(t_game *game)
{
    struct timeval tv;

    gettimeofday(&tv, NULL);
    game->time = tv.tv_sec + tv.tv_usec / 1000000.0;
    game->frameTime = game->time - game->oldTime;
    game->oldTime = game->time;
}

void    rotate_player(t_game *game, double rotationSpeed)
{
    double oldDirX;
    double oldPlaneX;
    game->angle += rotationSpeed * game->frameTime;
    oldDirX = game->dirX;
    game->dirX = cos(game->angle);
    game->dirY = sin(game->angle);
    oldPlaneX = game->planeX;
    game->planeX = -sin(game->angle) * FOV;
    game->planeY = cos(game->angle) * FOV;
}

void move_player(t_game *game, double moveSpeed)
{
    double nextX, nextY;

    if (game->keys.w)
    {
        nextX = game->posX + game->dirX * moveSpeed * game->frameTime;
        nextY = game->posY + game->dirY * moveSpeed * game->frameTime;
        if (nextX > 0 && nextX < game->map_width && nextY > 0 && nextY < game->map_height &&
            game->map[(int)nextY][(int)nextX] == '0')
        {
            game->posX = nextX;
            game->posY = nextY;
        }
    }
    if (game->keys.s)
    {
        nextX = game->posX - game->dirX * moveSpeed * game->frameTime;
        nextY = game->posY - game->dirY * moveSpeed * game->frameTime;
        if (nextX > 0 && nextX < game->map_width && nextY > 0 && nextY < game->map_height &&
            game->map[(int)nextY][(int)nextX] == '0')
        {
            game->posX = nextX;
            game->posY = nextY;
        }
    }
}











