/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 12:16:06 by ldick             #+#    #+#             */
/*   Updated: 2024/05/14 14:19:06 by ldick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

int	main(int argc, char *argv[])
{
	t_fractal	f;

	if (argc == 2 && ((!ft_strncmp(argv[1], "-m", 2) || (!ft_strncmp(argv[1], "-j", 2)))))
	{
		init_fractal(&f);
		fractal_render(&f);
		mlx_key_hook(f.mlx_window, my_key_handler, &f);
		mlx_scroll_hook(f.mlx_window, my_scroll_func, &f);
		mlx_loop(f.mlx_window);
	}
	return (0);
}
