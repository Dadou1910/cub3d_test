// void    check_map_copy(t_game *game, char **map_copy, int *x, int *y)
// {
//     while (*y < game->map_height)
//     {
//         *x = 0;
//         while (map_copy[*y][*x])
//         {
//             if (map_copy[*y][*x] == '0')
//             {
//                 printf("Error: Map contains inaccessible areas at line %d, column %d\n",
//                         *y + 1, *x + 1);
//                 clean_exit(game, game->mlx);
//             }
//             *x++;
//         }
//         free(map_copy[*y]);
//        (*y)++;
//     }
// }

// void validate_accessible_map(t_game *game)
// {
//     int y;
//     int x;
//     char **map_copy;
    
//     map_copy = malloc(sizeof(char *) * (game->map_height + 1));
//     if (!map_copy)
//         check_malloc(game, game->mlx);
//     y = 0;
//     while (y < game->map_height)
//     {
//         map_copy[y] = ft_strdup(game->map[y]);
//             check_malloc(game, game->mlx);
//         y++;
//     }
//     map_copy[y] = NULL;
//     flood_fill(map_copy, (int)game->posX, (int)game->posY, game);
//     y = 0;
//     while (y < game->map_height)
//     {
//         x = 0;
//         while (map_copy[y][x])
//         {
//             if (map_copy[y][x] == '0')
//             {
//                 printf("Error: Map contains inaccessible areas at line %d, column %d\n",
//                         y + 1, x + 1);
//                 clean_exit(game, game->mlx);
//             }
//             x++;
//         }
//         free(map_copy[y]);
//         y++;
//     }
//     free(map_copy);
// }