/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadou <dadou@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 01:25:41 by jealefev          #+#    #+#             */
/*   Updated: 2024/12/29 13:14:54 by dadou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int check_text(char *line)
{
    if ((strncmp(line, "NO ", 3) == 0) || 
        (strncmp(line, "SO ", 3) == 0) || 
        (strncmp(line, "WE ", 3) == 0) || 
        (strncmp(line, "EA ", 3) == 0) || 
        (strncmp(line, "F ", 2) == 0) || 
        (strncmp(line, "C ", 2) == 0))
        return (0);
    else
        return (1);
}

void    check_map_char(char *line, t_game *game)
{
    int x;

    x = 0;
    while (line[x])
    {
        if (line[x] != '0' && line[x] != '1' && line[x] != ' ' && line[x] != 'P') // Invalid char
        {
            printf("Error: Invalid character '%c' in map \n", line[x]);
            clean_exit(game, game->mlx);
        }
        x++;
    }
}

int    map_not_started(char *line, t_game *game)
{
    char    *test_line;
    
    test_line = trim_whitespace(line);
    if (line[0] == '\0' || line[0] == '\n')
        return (0);
    if (!check_text(test_line))// Textures and colors
        parse_config(test_line, game->mlx, game);
    else if (line[0] == '1' || line[0] == '0' || line[0] == ' ') // Map starts
        return (1);
    else
    {
        printf("Error: Invalid line -> %s", line);
        clean_exit(game, game->mlx);
    }
    return (0);
}

char    *map_has_started(t_game *game, char *line)
{
    int len;

    check_duplicate_or_missing(game, game->mlx);
    len = ft_strlen(line);
    if (len > 0 && line[len - 1] == '\n')
        line[len - 1] = '\0';
    check_map_char(line, game);
    return (line);
    
}

void parse_file(const char *filename, t_game *game, t_mlx *mlx)
{
    int     y;
    int     fd;
    int     map_started;
    char    *line;
    char    **map;

    fd = open(filename, O_RDONLY);
    if (fd < 0)
        cleanup_and_exit(game, mlx, "Couldn't open map file");
    y = 0;
    map_started = 0;
    if (!(map = malloc(sizeof(char *) * 4096)))
        check_malloc(game, mlx);
    while ((line = get_next_line(fd)))
    {
        if (map_started || (map_started = map_not_started(line, game)))
            map[y++] = ft_strdup(map_has_started(game, line));
        free(line);
    }
    map[y] = NULL;
    game->map = map;
    close(fd);
}

