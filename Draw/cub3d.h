/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 12:35:06 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/07/18 06:09:57 by oaboulgh         ###   ########.fr       */
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
# define MOVE_SPEED 2
// # define ROTATION_SPEED 0.01
# define NUM_OF_RAYS 960
# define VIEW_ANGLE 60 // in degree
# define DG 0.01745329 // one degree in radian
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

typedef struct s_player
{
	char	**map;
	double	x;
	double	y;
	int		radius;
	int		turn_d;
	int		walk_d;
	int		rotate_left;
	int		rotate_right;
	int		move_forward;
	int		move_backward;
	double	rotation_angle;
	double	rotation_speed;
	int		move_speed;
}	t_player;

typedef struct s_cub
{
	struct s_player	*player;
	void			*img;
	void			*mlx;
	void			*mlx_win;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
}	t_cub;


void	init_player(t_player *player, char **map);
void	draw_player(t_cub *info, t_player *player);
int		has_wall(float x, float y, t_cub *info);
void	draw_circle(t_cub *info, t_player *player);
void	my_mlx_pixel_put(t_cub *data, int x, int y, int color);
void	dda(int X0, int Y0, int X1, int Y1, t_cub *info, int color);
void	draw_rays(t_cub *info);
void	cast_rays(t_cub *info, float ray_angle);

#endif
