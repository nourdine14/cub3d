/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 12:35:06 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/08/04 06:38:13 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <limits.h>

# define WIDTH_SIZE 32
# define S_WIDTH 16
# define MARGIN 0
# define PLAYER_S 5
# define G_SIZE 64
# define COL 15
# define ROW 11
# define MOVE_SPEED 6
# define ROTATION_SPEED 0.02
# define NUM_OF_RAYS 960
# define VIEW_ANGLE 60 // in degree
# define DG 0.01745329 // one degree in radian

# define MINI_MAP_SCALE 0.5
# define MAP_W 32

# define WALL_WIDTH 1
# define SPACE_FROM_WALL 16
# define TEXTURES_WIDTH 256
// # define HEIGHT COL * G_SIZE
// # define WIDTH

typedef struct s_var
{
	float	x;
	float	y;
	float	x1;
	float	y1;
	int		i;
	int		j;
}	t_var;

typedef struct	s_img
{
	void	*img_ptr; // MLX image pointer
	char	*addr;    // Pointer to the image data in memory
	int		bpp;      // Number of bits per pixel (e.g., 32 bits for 24-bit color + alpha)
	int		line_len; // Number of bytes per image row (including padding)
	int		endian;   // Endianness of the image data
	int		height;
	int		width;
}				t_img;

typedef struct s_ray
{
	float	xherizontalle_hit_wall;
	float	yherizontalle_hit_wall;
	float	xvertical_hit_wall;
	float	yvertical_hit_wall;
	float	ix;
	float	iy;
	float	ystep;
	float	xstep;
	float	xinter;
	float	yinter;
	int		i;
	int		j;
	bool	b;
	bool	a;
	float	xhit;
	float	yhit;
	float	ray_dist;
}	t_ray;

typedef struct s_player
{
	char	**map;
	float	x;
	float	y;
	float	mini_map_x;
	float	mini_map_y;
	float	mouse_x;
	float	mouse_y;
	float	middle_of_screen;
	int		radius;
	int		turn_d;
	int		walk_d;
	int		rotate_left;
	int		rotate_right;
	int		move_forward;
	int		move_backward;
	float	rotation_angle;
	float	rotation_speed;
	int		move_speed;
}	t_player;

typedef struct s_cub
{
	struct s_player	*player;
	void			*mlx;
	void			*mlx_win;
	t_img			img;
	t_img			map;
	t_img			side1;
	t_img			side2;
	t_img			side3;
	t_img			side4;
}	t_cub;


void	dda(int X0, int Y0, int X1, int Y1, t_cub *info, int color);
float	diff_of_two_points(float x, float y, float x1, float y1);
void	my_mlx_pixel_put(t_cub *data, int x, int y, int color);
void	cast_rays(t_cub *info, float ray_angle, int i);
void	draw_player(t_cub *info, t_player *player);
void	draw_circle(t_cub *info, t_player *player);
void	init_player(t_player *player, char **map);
bool	ray_lookig_left(double angle);
bool	ray_lookig_up(double angle);
float	scale_angle(float angle);
void	draw_rays(t_cub *info);

void	horizontale(t_cub *info, t_ray *ray, float ray_angle);
void	draw_wall(t_cub *info, t_ray *ray, float ray_angle, int i);
void	verticale(t_cub *info, t_ray *ray, float ray_angle);

int		long_line(char **map);
int		height_of_map(char **map);

int		has_wall(float x, float y, t_cub *info);
int		has_wall2(float x, float y, t_cub *info);

void	move_player(t_player *player, t_cub *info);

#endif
