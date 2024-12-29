/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_dist.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadou <dadou@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 01:25:41 by jealefev          #+#    #+#             */
/*   Updated: 2024/12/29 11:21:37 by dadou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void compute_ray_properties(t_game *game, t_ray *ray)
{
    ray->deltaDistX = (ray->rayDirX == 0) ? (1e30) : (fabs(1 / ray->rayDirX));
    ray->deltaDistY = (ray->rayDirY == 0) ? (1e30) : (fabs(1 / ray->rayDirY));
    ray->stepX = (ray->rayDirX < 0) ? (-1) : (1);
    ray->stepY = (ray->rayDirY < 0) ? (-1) : (1);
}

void calculate_side_dist(t_game *game, t_ray *ray)
{
    if (ray->rayDirX < 0)
        ray->sideDistX = ((game->posX - ray->mapX) * ray->deltaDistX);
    else
        ray->sideDistX = ((ray->mapX + 1.0 - game->posX) * ray->deltaDistX);

    if (ray->rayDirY < 0)
        ray->sideDistY = ((game->posY - ray->mapY) * ray->deltaDistY);
    else
        ray->sideDistY = ((ray->mapY + 1.0 - game->posY) * ray->deltaDistY);
}

void calculate_ray_direction(t_game *game, t_ray *ray)
{
    ray->cameraX = (2 * game->currentStripe / (double)WIDTH - 1);
    ray->rayDirX = game->dirX + game->planeX * ray->cameraX;
    ray->rayDirY = game->dirY + game->planeY * ray->cameraX;
}