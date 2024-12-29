/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadou <dadou@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 01:25:41 by jealefev          #+#    #+#             */
/*   Updated: 2024/12/29 11:38:35 by dadou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

char *trim_whitespace(char *str)
{
    int len;
    
    while (*str == ' ' || *str == '\t')
        str++;
    len = strlen(str);
    while (len > 0 && (str[len - 1] == ' ' || str[len - 1] == '\t' || str[len - 1] == '\n'))
    {
        str[len - 1] = '\0';
        len--;
    }
    return (str);
}

void load_texture(t_mlx *mlx, t_texture *texture, t_game *game, char *path)
{
    path = trim_whitespace(path); // Trim spaces for texture path
    texture->width = 64;
    texture->height = 64;
    texture->img = mlx_xpm_file_to_image(mlx->mlx, path, &texture->width, &texture->height);
    if (!texture->img)
        cleanup_and_exit(game, mlx, "Invalid texture path");
    texture->addr = mlx_get_data_addr(texture->img, &texture->bpp, &texture->line_len, &texture->endian);
}

int parse_value(char *line, int *i)
{
    int value;

    value = 0;
    while (line[*i] && line[*i] >= '0' && line[*i] <= '9')
        value = value * 10 + (line[(*i)++] - '0');
    return (value);
}

void validate_comma(t_game *game, char *line, int *i)
{
    if (line[*i] != ',')
    {
        printf("Error: Invalid format (missing or misplaced commas) -> %s\n", line);
        clean_exit(game, game->mlx);
    }
    (*i)++;
}

int parse_color(t_game *game, char *line)
{
    int r;
    int g;
    int b;
    int i;

    i = 0;
    line = trim_whitespace(line);
    r = parse_value(line, &i);
    validate_comma(game, line, &i);
    g = parse_value(line, &i);
    validate_comma(game, line, &i);
    b = parse_value(line, &i);

    // General error for any invalid value or extra characters
    if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255 || line[i] != '\0')
    {
        printf("Error: Invalid color value -> %s\n", line);
        clean_exit(game, game->mlx);
    }

    return ((r << 16) | (g << 8) | b);
}
