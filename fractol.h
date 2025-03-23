/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 09:28:09 by ldick             #+#    #+#             */
/*   Updated: 2025/03/23 20:39:27 by ldick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "MLX42/include/MLX42/MLX42.h"
# include "main-libs/libs.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <OpenCL/opencl.h>
// # include <OpenCL/cl.h>

typedef struct s_img
{
	void	*img_ptr;
	char	*pixel_ptr;
	int		bpp;
	int		endian;
	int		line_len;
}			t_img;

typedef struct s_gpu_calc
{
	cl_platform_id		platform_id;
	cl_device_id		device_id;
	cl_context			context;
	cl_command_queue	queue;
	cl_uint				num_platforms;
	cl_program			programm;
	const char			*kernelSource;
	cl_kernel			kernel;
	cl_int				error;
	cl_mem				image_buffer;
}				t_gpu_calc;

typedef struct s_fractal
{
	char		*name;
	void		*mlx_hooks;
	void		*mlx_window;
	t_img		img;
	double		escape_val;
	double		shift_x;
	double		shift_y;
	double		zoom;
	int			max_iterations;
	double		julia_x;
	double		julia_y;
	double		old_min;
	t_gpu_calc	gpu;
}			t_fractal;

typedef struct s_comp
{
	double	x;
	double	y;
}			t_comp;

# define WIDTH 800
# define HIGHT 800
# define DEFAULT_ITERATIONS 50
# define ZOOM 1
# define MOUSE_W_UP 4
# define MOUSE_W_DOWN 5
# define BLACK 0x000000
# define WHITE 0xFFFFFF
# define RED 0xFF0000
# define GREEN 0x00FF00
# define BLUE 0x0000FF
# define YELLOW 0xFFFF00
# define MAGENTA 0xFF00FF
# define CYAN 0x00FFFF
# define ORANGE 0xFFA500
# define PURPLE 0x800080
# define GRAY 0x808080
# define BROWN 0xA52A2A
# define PINK 0xFFC0CB
# define LIME 0x00FF00
# define TEAL 0x008080
# define OLIVE 0x808000
# define NAVY 0x000080
# define MAROON 0x800000
# define SILVER 0xC0C0C0
# define GOLD 0xFFD700
# define INDIGO 0x4B0082
# define VIOLET 0xEE82EE

// fractal sets
void		up_down_burning_ship(int x, int y, t_fractal *f);
void		mandelbrot(int x, int y, t_fractal *f);
void		julia(int x, int y, t_fractal *f);

// initialization
void		data_init(t_fractal *f);
void		z_and_y_init(t_comp *z);
void		init_fractal(t_fractal *f);
void		fancy_name_maker(t_fractal *f);
void		event_init(t_fractal *f);
void		julia_base_init(t_fractal *f);
int			mlx_argv_check(int argc, char **argv, t_fractal *f);

//math
t_comp		square_complex(t_comp z);
t_comp		sum_complex(t_comp z1, t_comp z2);
double		map(double unscaled, double new_min, double new_max,
				double old_max);

//events
void		my_scroll_func(double xdelta, double ydelta, void *param);
void		my_key_handler(mlx_key_data_t mkd, void *data);

//rendering
void		fractal_render(t_fractal *f);

void		leakcheck(void);
void		info_message(void);

#endif