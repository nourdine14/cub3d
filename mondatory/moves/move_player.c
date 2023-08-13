/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakebli <nakebli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 18:06:23 by nakebli           #+#    #+#             */
/*   Updated: 2023/08/13 19:06:08 by nakebli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	move_player2(t_cub *info, float dx, float dy)
{
	if (info->player->move_forward_l \
	&& !has_wall2(info->player->x + dy, info->player->y, info))
		info->player->x += dy;
	if (info->player->move_forward_l \
	&& !has_wall2(info->player->x, info->player->y - dx, info))
		info->player->y -= dx;
	if (info->player->move_forward_r \
	&& !has_wall2(info->player->x - dy, info->player->y, info))
		info->player->x -= dy;
	if (info->player->move_forward_r \
	&& !has_wall2(info->player->x, info->player->y + dx, info))
		info->player->y += dx;
	if (info->player->move_forward \
	&& !has_wall2(info->player->x + dx, info->player->y, info))
		info->player->x += dx;
	if (info->player->move_forward \
	&& !has_wall2(info->player->x, info->player->y + dy, info))
		info->player->y += dy;
	if (info->player->move_backward \
	&& !has_wall2(info->player->x - dx, info->player->y, info))
		info->player->x -= dx;
	if (info->player->move_backward \
	&& !has_wall2(info->player->x, info->player->y - dy, info))
		info->player->y -= dy;
}

void	redraw_in_move(t_cub *info, t_player *player, int counter)
{
	info->gun1.img_ptr = mlx_xpm_file_to_image(info->mlx, "textures/gun2.xpm", \
	player->x1, player->y1);
	free(info->gun1.addr);
	info->gun1.addr = mlx_get_data_addr(info->gun1.img_ptr, &info->gun1.bpp, \
		&info->gun1.line_len, &info->gun1.endian);
	if (counter > 10)
	{
		player->shot = 0;
		player->stop = 1;
		counter = 0;
	}
}

void	move_player(t_player *player, t_cub *info)
{
	float		angle;
	float		dx;
	float		dy;
	static int	counter;

	if (!player->shot)
		counter = 0;
	angle = player->rotation_angle;
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
		redraw_in_move(info, player, counter);
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
