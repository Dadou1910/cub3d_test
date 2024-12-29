/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadou <dadou@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 01:25:41 by jealefev          #+#    #+#             */
/*   Updated: 2024/12/29 11:38:57 by dadou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void render_ceiling(t_mlx *mlx, int color)
{
    int x;
    int y;

    y = 0;
    while (y < HEIGHT / 2)
    {
        x = 0;
        while (x < WIDTH)
        {
            my_mlx_pixel_put(mlx, x, y, color);
            x++;
        }
        y++;
    }
}

void render_floor(t_mlx *mlx, int color)
{
    int x;
    int y;

    y = HEIGHT / 2;
    while (y < HEIGHT)
    {
        x = 0;
        while (x < WIDTH)
        {
            my_mlx_pixel_put(mlx, x, y, color);
            x++;
        }
        y++;
    }
}

void draw_textured_column(t_game *game, t_mlx *mlx, int x, int drawStart, int drawEnd, int side, t_texture *texture, int texX)
{
    double step;
    double texPos;
    int y;
    int texY;
    int color;

    step = 1.0 * texture->height / (drawEnd - drawStart);
    texPos = (drawStart < 0) ? -drawStart * step : 0.0;
    if (drawEnd >= HEIGHT)
        drawEnd = HEIGHT - 1;
    y = drawStart < 0 ? 0 : drawStart;
    while (y < drawEnd)
    {
        texY = (int)texPos & (texture->height - 1);
        texPos += step;
        color = *(unsigned int *)(texture->addr + (texY * texture->line_len + texX * (texture->bpp / 8)));
        if (side == 1)
            color = (color >> 1) & 0x7F7F7F;
        my_mlx_pixel_put(mlx, x, y, color);
        y++;
    }
}

void render_textured_column(t_game *game, t_mlx *mlx, int x, int drawStart, int drawEnd, int side, double wallX)
{
    t_texture *texture;
    int texX;

    texture = select_texture(game, mlx, side);
    texX = (int)(wallX * (double)texture->width);
    if ((side == 0 && game->ray.rayDirX > 0) || (side == 1 && game->ray.rayDirY < 0))
        texX = texture->width - texX - 1;
    draw_textured_column(game, mlx, x, drawStart, drawEnd, side, texture, texX);
}


void render_frame(t_game *game, t_ray *ray, char **map, t_mlx *mlx)
{
    int stripe = 0;
    clear_screen(mlx);
    render_ceiling(mlx, mlx->ceiling_color);
    render_floor(mlx, mlx->floor_color);
    while (stripe < WIDTH)
    {
        game->currentStripe = stripe;
        ray->mapX = (int)game->posX;
        ray->mapY = (int)game->posY;
        process_raycasting(game, ray, mlx);
        stripe++;
    }
    mlx_put_image_to_window(mlx->mlx, mlx->mlx_win, mlx->img, 0, 0);
}