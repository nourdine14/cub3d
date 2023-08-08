/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakebli <nakebli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 13:08:29 by nakebli           #+#    #+#             */
/*   Updated: 2023/08/08 10:42:11 by nakebli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "parcing/parcing.h"

void	ft(void)
{
	system("leaks cub3D");
}

int	main(int ac, char **av)
{
	t_info	*info;
	t_cub	*cub;
	int		i;

	i = 0;
	// atexit(ft);
	if (ac != 2)
	{
		printf("Error\n");
		exit(0);
	}
	info = parcing(av[1], &cub);
	while (info->map[i])
	{
		free(info->map[i]);
		i++;
	}
	// cub->mlx = mlx_init();
	// cub->win = mlx_new_window(cub->mlx, 500, 500, "Cub3D");
	// mlx_loop(cub->mlx);
	return (0);
}
