/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 19:09:59 by nakebli           #+#    #+#             */
/*   Updated: 2023/08/20 19:35:42 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	free_2d(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

static void	exit_and_free(t_cub *info)
{
	mlx_destroy_window(info->mlx, info->mlx_win);
	free_2d(info->info->no);
	free_2d(info->info->ea);
	free_2d(info->info->so);
	free_2d(info->info->we);
	free(info->info);
	free(info->doors_pos);
	exit (0);
}

int	handle_keypress(int keycode, void *param)
{
	t_cub	*info;

	info = (t_cub *)param;
	if (keycode == 53)
		exit_and_free(info);
	if (keycode == 36)
		info->player->open = 1;
	else if (keycode == 51)
		info->player->open = 0;
	else if (keycode == 0)
		info->player->move_forward_l = 1;
	else if (keycode == 2)
		info->player->move_forward_r = 1;
	else if (keycode == 49 && !info->player->stop)
		info->player->shot = 1;
	else if (keycode == 13)
		info->player->move_forward = 1;
	else if (keycode == 1)
		info->player->move_backward = 1;
	else if (keycode == 123)
		info->player->rotate_left = 1;
	else if (keycode == 124)
		info->player->rotate_right = 1;
	return (0);
}

int	handle_keyrelease(int keycode, void *param)
{
	t_cub	*info;

	info = (t_cub *)param;
	if (keycode == 0)
		info->player->move_forward_l = 0;
	if (keycode == 2)
		info->player->move_forward_r = 0;
	if (keycode == 49)
	{
		info->player->shot = 0;
		info->player->stop = 0;
	}
	if (keycode == 13)
		info->player->move_forward = 0;
	if (keycode == 36)
		info->player->open = -1;
	else if (keycode == 51)
		info->player->open = -1;
	else if (keycode == 1)
		info->player->move_backward = 0;
	else if (keycode == 123)
		info->player->rotate_left = 0;
	else if (keycode == 124)
		info->player->rotate_right = 0;
	return (0);
}

int	get_sign(float nbr)
{
	if (nbr >= 0)
		return (1);
	return (-1);
}
