/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 12:39:05 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/07/10 22:13:16 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_square(void *mlx, void *mlx_win, int i, int j, int color)
{
	int	a;
	int	b;

	b = i;
	a = j;
	while (i < (b + G_SIZE - 1))
	{
		j = a;
		while (j < (a + G_SIZE - 1))
		{
			mlx_pixel_put(mlx, mlx_win, i, j, color);
			j++;
		}
		i++;
	}
}

void	draw_player(void *mlx, void *mlx_win, int x, int y)
{
	int	a;
	int	b;

	a = x - PLAYER_S;
	b = y - PLAYER_S;
	printf("%d\n", a);
	exit (0);
	while (a < x + (PLAYER_S * 2))
	{
		b = y - PLAYER_S;
		while (b < y + (PLAYER_S * 2))
		{
			mlx_pixel_put(mlx, mlx_win, a, b, 0xFFFFFF);
			b++;
		}
		a++;
	}
}

void	draw_map(void *mlx, void *mlx_win, char **map)
{
	int	i;
	int	j;
	int	a;
	int	b;

	i = 0;
	j = 0;
	a = MARGIN;
	b = MARGIN;
	while (i < ROW)
	{
		j = 0;
		b = MARGIN;
		while (j < COL)
		{
			if (map[i][j] == '1')
				draw_square(mlx, mlx_win, j * G_SIZE, i * G_SIZE, 0xFFFFFF);
			if (map[i][j] == '0')
				draw_square(mlx, mlx_win, j * G_SIZE, i * G_SIZE, 0xccf2ff);
			j++;
			b += G_SIZE;
		}
		printf("\n");
		a += 32;
		i++;
	}
}

char	**ft_get_map(char *file)
{
	char	**map;
	return (map);
}

int	main(int ac, char **av)
{
	void	*mlx;
	void	*mlx_win;
	char *grid[] = {
        // "11111111111",
        // "10000000111",
        // "10011100001",
        // "10000000111",
        // "10000000011",
        // "11000001011",
        // "11100001011",
        // "11111111111",
        "111111111111111",
        "100000000000101",
        "100101000000101",
        "111110000010101",
        "100000000010101",
        "100000001111101",
        "100000000000001",
        "100000000000001",
        "111111000111101",
        "100000000000001",
        "111111111111111"
    };
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, COL * G_SIZE, ROW * G_SIZE, "Cub3D");
	draw_map(mlx, mlx_win, grid);
	mlx_loop(mlx);
	return (0);
}
