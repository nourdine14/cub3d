/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 05:14:00 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/08/19 18:38:54 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
	info->side4.img_ptr = mlx_xpm_file_to_image(info->mlx, \
	info->info->ea[1], &x, &y);
	if (!info->side4.img_ptr)
		print_errors("Error image couldn't load");
	info->side4.addr = mlx_get_data_addr(info->side4.img_ptr, \
	&info->side4.bpp, &info->side4.line_len, &info->side4.endian);
	info->side4.height = y;
	info->side4.width = x;
}

void	full_images2(t_cub *info, int x, int y)
{
	info->side1.addr = mlx_get_data_addr(info->side1.img_ptr, \
	&info->side1.bpp, &info->side1.line_len, &info->side1.endian);
	info->side1.height = y;
	info->side1.width = x;
	info->side2.img_ptr = mlx_xpm_file_to_image(info->mlx, \
	info->info->so[1], &x, &y);
	if (!info->side2.img_ptr)
		print_errors("Error image couldn't load");
	info->side2.addr = mlx_get_data_addr(info->side2.img_ptr, \
	&info->side2.bpp, &info->side2.line_len, &info->side2.endian);
	info->side2.height = y;
	info->side2.width = x;
	info->side3.img_ptr = mlx_xpm_file_to_image(info->mlx, \
	info->info->we[1], &x, &y);
	if (!info->side3.img_ptr)
		print_errors("Error image couldn't load");
	info->side3.addr = mlx_get_data_addr(info->side3.img_ptr, \
	&info->side3.bpp, &info->side3.line_len, &info->side3.endian);
	info->side3.height = y;
	info->side3.width = x;
	full_images3(info, x, y);
}

void	full_images(t_cub *info)
{
	int	x;
	int	y;

	info->img.img_ptr = mlx_new_image(info->mlx, COL * G_SIZE, ROW * G_SIZE);
	if (!info->img.img_ptr)
		print_errors("Error image couldn't load");
	info->img.addr = mlx_get_data_addr(info->img.img_ptr, &info->img.bpp, \
		&info->img.line_len, &info->img.endian);
	info->side1.img_ptr = mlx_xpm_file_to_image(info->mlx, \
	info->info->no[1], &x, &y);
	if (!info->side1.img_ptr)
		print_errors("Error image couldn't load");
	full_images2(info, x, y);
}

int	move_and_draw(void *param)
{
	t_cub	*info;

	info = (t_cub *)param;
	full_images(info);
	color_background(info);
	draw_rays(info);
	move_player(info->player, info);
	mlx_clear_window(info->mlx, info->mlx_win);
	mlx_put_image_to_window(info->mlx, info->mlx_win, info->img.img_ptr, 0, 0);
	mlx_destroy_image(info->mlx, info->img.img_ptr);
	return (0);
}
