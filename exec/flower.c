/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flower.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadou <dadou@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 01:25:41 by jealefev          #+#    #+#             */
/*   Updated: 2024/12/29 12:50:25 by dadou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void render_flower_scaled_pixel(t_mlx *mlx, int x, int y, int scale, int color)
{
    int i;
    int j;

    i = 0;
    while (i < scale)
    {
        j = 0;
        while (j < scale)
        {
            my_mlx_pixel_put(mlx, x + i, y + j, color);
            j++;
        }
        i++;
    }
}

void render_flower_tile(t_mlx *mlx, t_texture *flower_texture, int x, int y, int scale, int start_x, int start_y)
{
    int texX;
    int texY;
    int color;
    int scaled_x;
    int scaled_y;

    texX = x;
    texY = y % flower_texture->height;
    color = *(unsigned int *)(flower_texture->addr +
                              (texY * flower_texture->line_len + texX * (flower_texture->bpp / 8)));
    if (color != 0xFF000000)
    {
        scaled_x = start_x + (x * scale);
        scaled_y = start_y + (y * scale);
        render_flower_scaled_pixel(mlx, scaled_x, scaled_y, scale, color);
    }
}

void render_flower(t_mlx *mlx, t_texture *flower_texture, int offset)
{
    int x;
    int y;
    int scale;
    int start_x;
    int start_y;

    y = 0;
    scale = HEIGHT / flower_texture->height;
    start_x = WIDTH - (flower_texture->width * scale) - 200;
    start_y = HEIGHT - (flower_texture->height * scale) + offset;

    while (y < flower_texture->height)
    {
        x = 0;
        while (x < flower_texture->width)
        {
            render_flower_tile(mlx, flower_texture, x, y, scale, start_x, start_y);
            x++;
        }
        y++;
    }
}

void animate_flower(t_game *game, t_mlx *mlx)
{
    static int direction;
    static int offset;
    static int frame_count;

    if (!game->init)
    {
        direction = 1;
        offset = 0;
        frame_count = 0;
    }
    if (game->keys.w || game->keys.s)
    {
        frame_count++;
        if (frame_count % 2 == 0)
        {
            offset += direction;
            if (offset > 10)
                direction = -1;
            else if (offset < 0)
                direction = 1;
        }
    }
    else
        offset = 0;
    render_flower(mlx, &mlx->flower_texture, offset);
}


