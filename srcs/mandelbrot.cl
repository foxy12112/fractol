# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    mandelbrot.cl                                      :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ldick <ldick@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/23 18:17:14 by ldick             #+#    #+#              #
#    Updated: 2025/03/23 19:03:25 by ldick            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#include "fractol"

__kernel void	mandelbrot_kernel(__global int *image, int width, int height, float zoom, float shift_x, float shift_y, int max_iterations, float escape_val)
{
	int		x;
	int		y;
	float2	z;
	float2	c;
	int		i;
	float	temp;

	x = get_global_id(0);
	y = get_global_id(1);
	if (x >= width || y >= height)
		return ;
	z = (float2)(0.0f, 0.0f);
	i = 0;
	c.x = (float)(x) / width * 4.0f - 2.0f;
	c.y = (float)(x) / height * 4.0f - 2.0f;
	c.x = c.x * zoom + shift_x;
	c.y = c.y * zoom + shift_y;
	while(1 < max_iterations)
	{
		temp = z.x * z.x - z.y * z.y + c.x;
		z.y = 2.0f * z.x * z.y + c.y;
		z.x = temp;
		if ((z.x * z.x + z.y * z.y) > escape_val)
		{
			int color = (i * x) % 256;
			image[y * width + x] = (color << 16) | (color << 8) | color;
			return ;
		}
		i++;
	}
	image[y * width + x] = 0xFFD700;
}