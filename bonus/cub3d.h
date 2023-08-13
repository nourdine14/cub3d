/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 12:35:06 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/08/13 16:18:07 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdbool.h>
# include <limits.h>
# include "get_next_line/get_next_line.h"

# define WIDTH_SIZE 32
# define S_WIDTH 16
# define MARGIN 0
# define PLAYER_S 5
# define G_SIZE 64
# define COL 15
# define ROW 11
# define MOVE_SPEED 4
# define ROTATION_SPEED 0.05
# define NUM_OF_RAYS 960
# define VIEW_ANGLE 60 // in degree
# define DG 0.01745329 // one degree in radian

# define MINI_MAP_SCALE 0.5
# define MAP_W 32

# define WALL_WIDTH 1
# define SPACE_FROM_WALL 10
# define TEXTURES_WIDTH 256
// # define HEIGHT COL * G_SIZE
// # define WIDTH

typedef struct	s_sprite
{
    int type;	// key , enemy
	int	state; // on off
	int	map; // which texture
	// position
	int	x;
	int	y;
	int	z;
}	t_sprite;

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
	t_img	sprite;
	char	**map;
	float	x;
	float	y;
	float	x1;
	float	y1;
	float	mouse_x;
	float	mouse_y;
	float	middle_of_screen;
	int		radius;
	int		turn_d;
	int		walk_d;
	int		rotate_left;
	int		rotate_right;
	int		shot;
	int		stop;
	int		move_forward;
	int		move_backward;
	int		move_forward_l;
	int		move_forward_r;
	float	rotation_angle;
	float	rotation_speed;
	int		move_speed;
	int		hp;
}	t_player;

typedef struct s_cub
{
	struct s_player	*player;
	void			*mlx;
	void			*mlx_win;
	bool			open_door;
	int				*doors_position;
	int				num_of_doors;;
	t_sprite		enemy;
	t_img			img;
	t_img			gun1;
	t_img			door;
	t_img			doorside;
	t_img			side1;
	t_img			side2;
	t_img			side3;
	t_img			side4;
}	t_cub;

typedef struct s_cubt
{
	void					*mlx;
	void					*win;
	char					*line;
	struct s_info			*info;
	struct s_cubt			*next;
	struct s_cubt			*prev;
}	t_cubt;

typedef struct s_info
{
	char	**no;
	char	**so;
	char	**ea;
	char	**we;
	int		f[3];
	int		c[3];
	char	**map;
	int		px;
	int		py;
	int		height;
}	t_info;

t_info	*parcing(char *av, t_cubt **cub);
char	*get_next_line(int fd);
void	print_map(t_cubt *cub);

void	dda(int X0, int Y0, int X1, int Y1, t_cub *info, int color);
float	diff_of_two_points(float x, float y, float x1, float y1);
void	my_mlx_pixel_put(t_img *data, int x, int y, int color);
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
int		handle_mouse_move(int x, int y, t_cub *info);
int		move_and_draw(void *param);

void	color_background(t_cub *info);
void	draw_map(t_cub *info, char **map);

void	draw_sprite(t_cub *info);

int		is_door(float x, float y, t_cub *info);
int		is_valid(float x, float y, t_cub *info);

#endif
