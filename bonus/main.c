/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakebli <nakebli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 12:39:05 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/08/13 21:19:09 by nakebli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_square(t_cub *info, int i, int j, int color)
{
	int	a;
	int	b;

	b = i;
	a = j;
	while (i < (b + G_SIZE * MINI_MAP_SCALE))
	{
		j = a;
		while (j < (a + G_SIZE * MINI_MAP_SCALE))
		{
			if (i >= 0 && j >= 0 && i <= 200 && j <= 200)
				my_mlx_pixel_put(&info->img, i, j, color);
			j++;
		}
		i++;
	}
}

void	draw_map(t_cub *info, char **map)
{
	int	i;
	int	j;
	int	a;
	int	b;

	i = 0;
	b = 100 - info->player->y * MINI_MAP_SCALE;
	while (map[i])
	{
		j = 0;
		a = 100 - info->player->x * MINI_MAP_SCALE;
		while (map[i][j])
		{
			if (map[i][j] == '1')
				draw_square(info, a, b, 0xFFFFFF);
			else if (map[i][j] == ' ')
				draw_square(info, a, b, 0x000000);
			else
				draw_square(info, a, b, 0xccf2ff);
			a += G_SIZE * MINI_MAP_SCALE;
			j++;
		}
		b += G_SIZE * MINI_MAP_SCALE;
		i++;
	}
}

int	close_win(void *param)
{
	t_cub	*info;

	info = (t_cub *)param;
	mlx_destroy_window(info->mlx, info->mlx_win);
	exit (0);
	return (0);
}

void	drawing_and_hook(t_cub info)
{
	mlx_hook(info.mlx_win, 17, 0, close_win, &info);
	mlx_hook(info.mlx_win, 2, 0, handle_keypress, &info);
	mlx_hook(info.mlx_win, 3, 0, handle_keyrelease, &info);
	mlx_hook(info.mlx_win, 6, 0, handle_mouse_move, &info);
	mlx_loop_hook(info.mlx, move_and_draw, &info);
}

int	main(int ac, char **av)
{
	t_cub		info;
	t_player	player;
	t_info		*info2;
	t_cubt		*cub;

	(void)ac;
	(void)av;
	if (ac != 2)
		print_errors("Error !");
	info2 = parcing(av[1], &cub);
	(void)av;
	(void)ac;
	info.player = &player;
	init_player(&player, info2->map);
	info.mlx = mlx_init();
	if (info.mlx == NULL)
		return (printf("Error init window\n"), 1);
	info.mlx_win = mlx_new_window(info.mlx, COL * 64, \
		ROW * 64, "Cub3D");
	drawing_and_hook(info);
	mlx_loop(info.mlx);
	return (0);
}
