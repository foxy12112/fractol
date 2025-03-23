/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 17:38:51 by ldick             #+#    #+#             */
/*   Updated: 2025/03/23 18:16:14 by ldick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

int	get_color(int r, int g, int b, int a)
{
	return ((r & 0xff) << 24 | (g & 0xff) << 16 | (b & 0xff) << 8 | (a & 0xff) << 0);
}

void	mandelbrot(int x, int y, t_fractal *f)
{
	t_comp	z;
	t_comp	c;
	int		i;
	int		color;

	i = 0;
	z.x = 0;
	z.y = 0;
	c.x = (map(x, -2, +2, WIDTH) * f->zoom) + f->shift_x;
	c.y = (map(y, +2, -2, HIGHT) * f->zoom) + f->shift_y;
	while (i < f->max_iterations)
	{
		z = sum_complex(square_complex(z), c);
		if ((z.x * z.x) + (z.y * z.y) > f->escape_val)
		{
			// color = map(i, BLACK, WHITE, f->max_iterations);
			color = get_color((i * x) % 256, (i * y) % 256, (i * (int)c.x - (int)c.y) % 256, 140);
			mlx_put_pixel(f->img.img_ptr, x, y, color);
			return ;
		}
		i++;
	}
	mlx_put_pixel(f->img.img_ptr, x, y, GOLD);
}

void	fractal_render(t_fractal *f)
{
	int	x;
	int	y;

	y = -1;
	while (++y < HIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			if (!ft_strcmp(f->name, "Mandelbrot"))
				mandelbrot(x, y, f);
			else if (!ft_strcmp(f->name, "Julia"))
				julia(x, y, f);
			else if (!ft_strcmp(f->name, "Burning_Ship"))
				up_down_burning_ship(x, y, f);
		}
	}
}

void	up_down_burning_ship(int x, int y, t_fractal *f)
{
	t_comp	z;
	t_comp	c;
	t_comp	z_temp;
	int		i;
	int		color;

	i = 0;
	c.x = (map(x, -2, +2, WIDTH) * f->zoom) + f->shift_x;
	c.y = (map(y, +2, -2, HIGHT) * f->zoom) + f->shift_y;
	z_and_y_init(&z);
	while (i < f->max_iterations)
	{
		z_temp = z;
		z.x = fabs(z_temp.x);
		z.y = fabs(z_temp.y);
		z = sum_complex(square_complex(z), c);
		if ((z.x * z.x) + (z.y * z.y) > f->escape_val)
		{
			color = get_color((i * (int)(x + y)) % 256, (i * (int)(y * x)) % 256, (i * (int)(y - x)) % 256, 140);
			mlx_put_pixel(f->img.img_ptr, x, y, color);
			return ;
		}
		i++;
	}
	mlx_put_pixel(f->img.img_ptr, x, y, GOLD);
}

void	julia(int x, int y, t_fractal *f)
{
	t_comp	z;
	t_comp	c;
	int		i;
	int		color;

	i = 0;
	z.x = (map(x, -2, +2, WIDTH) * f->zoom) + f->shift_x;
	z.y = (map(y, +2, -2, HIGHT) * f->zoom) + f->shift_y;
	c.x = f->julia_x;
	c.y = f->julia_y;
	while (i < f->max_iterations)
	{
		z = sum_complex(square_complex(z), c);
		if ((z.x * z.x) + (z.y * z.y) > f->escape_val)
		{
			color = map(i, BLACK, WHITE, f->max_iterations);
			mlx_put_pixel(f->img.img_ptr, x, y, color);
			return ;
		}
		i++;
	}
	mlx_put_pixel(f->img.img_ptr, x, y, GOLD);
}
