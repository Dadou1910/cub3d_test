/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadou <dadou@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 01:25:41 by jealefev          #+#    #+#             */
/*   Updated: 2024/12/29 10:56:52 by dadou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int    helper_ddaX(t_game *game)
{
    game->ray.sideDistX += game->ray.deltaDistX;
    game->ray.mapX += game->ray.stepX;
    return (0);
}

int    helper_ddaY(t_game *game)
{
    game->ray.sideDistY += game->ray.deltaDistY;
    game->ray.mapY += game->ray.stepY;
    return (1);
}

void perform_dda(t_game *game, char **map, int *hit, int *side)
{
    *hit = 0;
    
    while (*hit == 0)
    {
        if (game->ray.mapX < 0 || game->ray.mapX >= game->map_width || 
            game->ray.mapY < 0 || game->ray.mapY >= game->map_height || !map[game->ray.mapY][game->ray.mapX])
        {
            printf("Error pos: game->ray out of bounds at (%d, %d)\n", game->ray.mapX, game->ray.mapY);
            clean_exit(game, game->mlx);
        }
        if (game->ray.sideDistX < game->ray.sideDistY)
            *side = helper_ddaX(game);
        else
            *side = helper_ddaY(game);
        if (game->ray.mapX < 0 || game->ray.mapX >= game->map_width || 
            game->ray.mapY < 0 || game->ray.mapY >= game->map_height || !map[game->ray.mapY][game->ray.mapX])
        {
            printf("Error pos: game->ray out of bounds at (%d, %d)\n", game->ray.mapX, game->ray.mapY);
            clean_exit(game, game->mlx);
        }
        if (map[game->ray.mapY][game->ray.mapX] == '1')
            *hit = 1;
    }
}

void    help_raycasting(t_game *game, t_ray *ray, double *perp_wall_dist, int side)
{
    if (side == 0)
        *perp_wall_dist = (ray->mapX - game->posX
        + (1 - ray->stepX) / 2) / ray->rayDirX;
    else
        *perp_wall_dist = (ray->mapY - game->posY
        + (1 - ray->stepY) / 2) / ray->rayDirY;
    if (*perp_wall_dist < 0.01)
        *perp_wall_dist = 0.01;
}

void process_raycasting(t_game *game, t_ray *ray, t_mlx *mlx)
{
    int hit;
    int side;
    double perp_wall_dist;
    int line_height;
    int draw_start;
    int draw_end;
    double wallX;

    hit = 0;
    calculate_ray_direction(game, ray);
    compute_ray_properties(game, ray);
    calculate_side_dist(game, ray);
    perform_dda(game, game->map, &hit, &side);
    help_raycasting(game, ray, &perp_wall_dist, side);
    line_height = (int)(HEIGHT / perp_wall_dist);
    draw_start = -line_height / 2 + HEIGHT / 2;
    draw_end = line_height / 2 + HEIGHT / 2;
    if (side == 0)
        wallX = game->posY + perp_wall_dist * ray->rayDirY;
    else
        wallX = game->posX + perp_wall_dist * ray->rayDirX;
    wallX -= (int)wallX;
    render_textured_column(game, mlx, game->currentStripe, draw_start,
        draw_end, side, wallX);
}



