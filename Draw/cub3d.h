/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 12:35:06 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/07/11 18:56:45 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define WIDTH_SIZE 32
# define S_WIDTH 16
# define MARGIN 0
# define PLAYER_S 5
# define G_SIZE 64
# define COL 15
# define ROW 11
// # define HEIGHT COL * G_SIZE
// # define WIDTH

typedef struct s_player
{
	char	**map;
	int		x;
	int		y;
	int		radius;
	int		turn_d;
	int		walk_d;
	double	rotation_angle;
	double	rotation_speed;
	int		move_speed;
}	t_palyer;

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


void	init_player(t_palyer *player, char **map);
int		has_a_wall(char **map, int x, int y);
void	draw_circle(t_cub *info, t_palyer *player);
void	my_mlx_pixel_put(t_cub *data, int x, int y, int color);

#endif
