/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakebli <nakebli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 05:14:00 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/08/11 20:28:15 by nakebli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_player2(t_cub *info, float dx, float dy)
{
	if (info->player->move_forward_l \
	&& !has_wall2(info->player->x1 + dy, info->player->y1, info))
		info->player->x1 += dy;
	if (info->player->move_forward_l \
	&& !has_wall2(info->player->x1, info->player->y1 - dx, info))
		info->player->y1 -= dx;
	if (info->player->move_forward_r \
	&& !has_wall2(info->player->x1 - dy, info->player->y1, info))
		info->player->x1 -= dy;
	if (info->player->move_forward_r \
	&& !has_wall2(info->player->x1, info->player->y1 + dx, info))
		info->player->y1 += dx;
	if (info->player->move_forward \
	&& !has_wall2(info->player->x1 + dx, info->player->y1, info))
		info->player->x1 += dx;
	if (info->player->move_forward \
	&& !has_wall2(info->player->x1, info->player->y1 + dy, info))
		info->player->y1 += dy;
	if (info->player->move_backward \
	&& !has_wall2(info->player->x1 - dx, info->player->y1, info))
		info->player->x1 -= dx;
	if (info->player->move_backward \
	&& !has_wall2(info->player->x1, info->player->y1 - dy, info))
		info->player->y1 -= dy;
	info->player->x = info->player->x1;
	info->player->y = info->player->y1;
}

void move_player(t_player *player, t_cub *info)
{
	int		x1;
	int		y1;
	float	angle;
	float	dx;
	float	dy;
	static int	counter;

	if (!player->shot)
		counter = 0;
	angle = player->rotation_angle;
	info->player->x1 = player->x;
	info->player->y1 = player->y;
	angle = scale_angle(angle);
	dx = cos(angle) * MOVE_SPEED;
	dy = sin(angle) * MOVE_SPEED;

	move_player2(info, dx, dy);

	if (player->rotate_left)
		player->rotation_angle -= ROTATION_SPEED;
	if (player->rotate_right)
		player->rotation_angle += ROTATION_SPEED;
	
	if (player->shot)
	{
		info->gun1.img_ptr = \
		mlx_xpm_file_to_image(info->mlx, "textures/gun2.xpm", &x1, &y1);
		free(info->gun1.addr);
		info->gun1.addr = \
		mlx_get_data_addr(info->gun1.img_ptr, &info->gun1.bpp, \
			&info->gun1.line_len, &info->gun1.endian);
		if (counter > 10)
		{
			player->shot = 0;
			player->stop = 1;
			counter = 0;
		}
	}
	counter++;
}

int	handle_mouse_move(int x, int y, t_cub *info)
{
	int	dx;
	int	dy;

	dx = x - info->player->mouse_x;
	dy = y - info->player->mouse_y;
	info->player->mouse_x = x;
	info->player->mouse_y = y;
	if (x < G_SIZE * COL && y < G_SIZE * ROW && x > 0 && y > 0)
		info->player->rotation_angle += 0.005 * dx;
	if (x < G_SIZE * COL && y < G_SIZE * ROW && x > 0 && y > 0 && \
		dy > 0 && info->player->middle_of_screen > 100)
		info->player->middle_of_screen -= 3;
	if (x < G_SIZE * COL && y < G_SIZE * ROW && x > 0 && y > 0 && \
		dy < 0 && info->player->middle_of_screen < (G_SIZE * ROW - 100))
		info->player->middle_of_screen += 3;
	return (0);
}

void	draw_hp_len(t_cub *info, int hp)
{
	int	i;
	int	j;

	j = 750;
	i = 50;
	while (i < (10 + 50))
	{
		j = 750;
		while (j < (hp + 750))
		{
			if (j >= 0 && j <= COL * G_SIZE && i >= 0 && i <= ROW * G_SIZE)
				my_mlx_pixel_put(&info->img, j, i, 0xff0000);
			j++;
		}
		i++;
	}
	j = 750;
	while (j++ < (hp + 750))
		my_mlx_pixel_put(&info->img, j, 49, 0xffffff);
	i = 48;
	while (i++ < 62)
		my_mlx_pixel_put(&info->img, 750, i, 0xffffff);
}

void	full_images3(t_cub *info, int x, int y)
{
	info->side4.img_ptr = mlx_xpm_file_to_image(info->mlx, "textures/side4.xpm", &x, &y);
	if (!info->side4.img_ptr)
	{
		printf("Error image couldn't load\n");
		exit (1);
	}
	info->side4.addr = mlx_get_data_addr(info->side4.img_ptr, &info->side4.bpp, &info->side4.line_len, &info->side4.endian);
	info->side4.height = y;
	info->side4.width = x;
	
	info->door.img_ptr = mlx_xpm_file_to_image(info->mlx, "textures/door.xpm", &x, &y);
	if (!info->door.img_ptr)
	{
		printf("Error image couldn't load\n");
		exit (1);
	}
	info->door.addr = mlx_get_data_addr(info->door.img_ptr, &info->door.bpp, &info->door.line_len, &info->door.endian);
	info->door.height = y;
	info->door.width = x;
}

void	full_images2(t_cub *info, int x, int y)
{
	info->side1.addr = mlx_get_data_addr(info->side1.img_ptr, &info->side1.bpp, &info->side1.line_len, &info->side1.endian);
	info->side1.height = y;
	info->side1.width = x;
	info->side2.img_ptr = mlx_xpm_file_to_image(info->mlx, "textures/sd1.xpm", &x, &y);
	if (!info->side2.img_ptr)
	{
		printf("Error image couldn't load\n");
		exit (1);
	}
	info->side2.addr = mlx_get_data_addr(info->side2.img_ptr, &info->side2.bpp, &info->side2.line_len, &info->side2.endian);
	info->side2.height = y;
	info->side2.width = x;
	info->side3.img_ptr = mlx_xpm_file_to_image(info->mlx, "textures/side3.xpm", &x, &y);
	if (!info->side3.img_ptr)
	{
		printf("Error image couldn't load\n");
		exit (1);
	}
	info->side3.addr = mlx_get_data_addr(info->side3.img_ptr, &info->side3.bpp, &info->side3.line_len, &info->side3.endian);
	info->side3.height = y;
	info->side3.width = x;
	full_images3(info, x, y);
}

void	full_images(t_cub *info)
{
	int	x;
	int	y;

	info->gun1.img_ptr = mlx_xpm_file_to_image(info->mlx, "textures/gun1.xpm", &x, &y);
	info->gun1.addr = mlx_get_data_addr(info->gun1.img_ptr, &info->gun1.bpp, \
		&info->gun1.line_len, &info->gun1.endian);
	
	info->img.img_ptr = mlx_new_image(info->mlx, long_line(info->player->map) * G_SIZE, \
		height_of_map(info->player->map) * G_SIZE);
	info->img.addr = mlx_get_data_addr(info->img.img_ptr, &info->img.bpp, \
		&info->img.line_len, &info->img.endian);
	
	info->side1.img_ptr = mlx_xpm_file_to_image(info->mlx, "textures/side1.xpm", &x, &y);
	if (!info->side1.img_ptr)
	{
		printf("Error image couldn't load\n");
		exit (1);
	}
	full_images2(info, x, y);
}

int	move_and_draw(void *param)
{
	t_cub	*info;

	info = (t_cub *)param;
	full_images(info);
	color_background(info);
	draw_rays(info);
	draw_map(info, info->player->map);
	draw_player(info, info->player);
	move_player(info->player, info);
	draw_hp_len(info, info->player->hp);
	
	mlx_clear_window(info->mlx, info->mlx_win);
	mlx_put_image_to_window(info->mlx, info->mlx_win, info->img.img_ptr, 0, 0);
	mlx_put_image_to_window(info->mlx, info->mlx_win, info->gun1.img_ptr, 450, 185);
	mlx_string_put(info->mlx, info->mlx_win, 750, 10, 0x000000 ,"Bullet : +99");
	mlx_destroy_image(info->mlx, info->img.img_ptr);
	return (0);
}
