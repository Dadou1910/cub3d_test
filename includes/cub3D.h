/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadou <dadou@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 14:01:59 by jealefev          #+#    #+#             */
/*   Updated: 2024/12/29 13:20:09 by dadou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "../Libft/libft.h"
# include "../minilib/mlx/mlx.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <errno.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/time.h>


#define WIDTH 1280
#define HEIGHT 720
#define ESC_KEY 65307
#define W_KEY 122
#define A_KEY 113
#define S_KEY 115
#define D_KEY 100
#define LEFT_ARROW 65361
#define RIGHT_ARROW 65363
#define UP_ARROW 65362
#define DOWN_ARROW 65364
#define TILE_SIZE 64
#define FOV 0.66
#define ROTATION_SPEED 1.9
#define MOVE_SPEED 3.3
#define MINIMAP_SIZE 150
#define TILE_SIZE_MINI 10
#define PLAYER_SIZE 4


typedef struct s_texture
{
    void    *img;
    char    *addr;
    int     width;
    int     height;
    int     bpp;
    int     line_len;
    int     endian;
}               t_texture;

typedef struct s_mlx
{
    void        *mlx;
    void        *mlx_win;
    void        *img;
    char        *addr;
    int         bits_per_pixel;
    int         line_length;
    int         endian;
	t_texture   north_texture;
    t_texture   south_texture;
    t_texture   east_texture;
    t_texture   west_texture;
    t_texture   flower_texture;
	int         floor_color;
    int         ceiling_color;
}   			t_mlx;

typedef struct s_ray
{
    double      rayDirX;
    double      rayDirY;
    double      deltaDistX;
    double      deltaDistY;
    double      sideDistX;
    double      sideDistY;
    double      cameraX;
    int         mapX;
    int         mapY;
    int         stepX;
    int         stepY;
}               t_ray;

typedef struct s_keys
{
    int         w;
    int         s;
    int         a;
    int         d;
}               t_keys;

typedef struct  s_minmap
{
    int         start_x;
    int         start_y;
    int         end_x;
    int         end_y;
}               t_minmap;

typedef struct s_game
{
    double      posX;
    double      posY;
    double      dirX;
    double      dirY;
    double      planeX;
    double      planeY;
    double      angle;
    double      time;
    double      oldTime;
    double      frameTime;
	int         currentStripe;
    int         map_width;
    int         map_height;
    int         count[6];
    char        **map;
    int         init;
    t_keys      keys;
	t_mlx		*mlx;
	t_ray		ray;
    t_minmap    minmap;
	
}               t_game;

//===================================================================//
//                      		 EXEC								 //
//===================================================================//

int		close_window(void *param);
int		key_press(int keycode, t_game *game);
void    init_game(t_game *game, t_mlx *mlx);
void    init_mlx(t_mlx *mlx);
void	init_ray(t_ray ray);
void    init_minmap(t_game *game);
void    rotate_player(t_game *game, double rotationSpeed);
void    move_player(t_game *game, double moveSpeed);
void    update_time(t_game *game);
void    key_events(t_game *game, t_mlx *mlx);
void	compute_ray_properties(t_game *game, t_ray *ray);
void	calculate_side_dist(t_game *game, t_ray *ray);
void	calculate_ray_direction(t_game *game, t_ray *ray);
void	process_raycasting(t_game *game, t_ray *ray, t_mlx *mlx);
void	render_frame(t_game *game, t_ray *ray, char **map, t_mlx *mlx);
void    render_textured_column(t_game *game, t_mlx *mlx, int x,
		int drawStart, int drawEnd, int side, double wallX);
void    my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color);
void    draw_flower(t_mlx *mlx, t_texture *flower, int frame_offset);
void    clear_screen(t_mlx *mlx);
void    render_minimap(t_game *game, t_mlx *mlx);
void    calculate_map_dimensions(t_game *game);
void    draw_tile(t_mlx *mlx, int x, int y, int color);
void    animate_flower(t_game *game, t_mlx *mlx);

//===================================================================//
//                      		 PARSING   							 //
//===================================================================//

int     parse_color(t_game *game, char *line);
int     help_walls(t_game *game, int x, int y);
int     is_valid_map_char(char c);
void    validate_config(t_mlx *mlx);
char    *trim_whitespace(char *str);
void    check_malloc(t_game *game, t_mlx *mlx);
void    load_texture(t_mlx *mlx, t_texture *texture, t_game *game, char *path);
void    check_duplicate_or_missing(t_game *game, t_mlx *mlx);
void    parse_file(const char *filename, t_game *game, t_mlx *mlx);
void    parse_config(char *line, t_mlx *mlx, t_game *game);
void    validate_map(t_game *game);
void    clean_exit(t_game *game, t_mlx *mlx);
void    cleanup_and_exit(t_game *game, t_mlx *mlx, const char *error_msg);
void    validate_config_map(char *line, t_game *game, t_mlx *mlx);
void    validate_accessible_map(t_game *game);
t_texture *select_texture(t_game *game, t_mlx *mlx, int side);
#endif