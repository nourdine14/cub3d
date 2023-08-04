/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 10:12:10 by oaboulgh          #+#    #+#             */
/*   Updated: 2023/07/30 10:28:17 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <mlx.h>

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

void	draw_image(void *mlx_ptr, void *mlx_win, t_img *img)
{
	int	i;
	int	j;
	int	offset;
	int	color;

	i = 0;
	j = 0;
	while (i < img->height)
	{
		j = 0;
		while (j < img->width)
		{
			offset = (i * img->line_len) + (j * (img->bpp / 8));
			color = *(int *)(img->addr + offset);
			mlx_pixel_put(mlx_ptr, mlx_win, j + 250, i + 250, color);
			j++;
		}
		i++;
	}
	
	
}

int32_t main(int32_t argc, const char* argv[])
{
	void	*mlx_win;
	void	*mlx_ptr;
	t_img	img;
	int		x;
	int		y;

	mlx_ptr = mlx_init();
	mlx_win = mlx_new_window(mlx_ptr, 600, 600, "xpm");
	img.img_ptr = mlx_xpm_file_to_image(mlx_ptr, "side1.xpm", &x, &y);
	img.addr = mlx_get_data_addr(img.img_ptr, &img.bpp, &img.line_len, &img.endian);
	img.height = y;
	img.width = x;
	printf("len = %d\n", img.line_len);
	draw_image(mlx_ptr, mlx_win, &img);
	mlx_loop(mlx_ptr);
	return (EXIT_SUCCESS);
}