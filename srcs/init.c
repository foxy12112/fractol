/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 09:26:30 by ldick             #+#    #+#             */
/*   Updated: 2025/03/23 21:21:03 by ldick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

static const char *load_kernel(const char *filename)
{
	FILE	*file;
	size_t	size;
	char	*kernel;

	file = fopen(filename, "r");
	if (!file)
		exit (1);
	fseek(file, 0, SEEK_END);
	size = ftell(file);
	rewind(file);
	kernel = (char *)malloc(size + 1);
	fread(kernel, 1, size, file);
	kernel[size] = '\0';
	fclose(file);
	return (kernel);
}

void	data_init(t_fractal *f)
{
	f->escape_val = 4;
	f->shift_x = 0.0;
	f->shift_y = 0.0;
	f->zoom = 1;
	f->max_iterations = DEFAULT_ITERATIONS;
// 	clGetPlatformIDs(1, &f->gpu.platform_id, &f->gpu.num_platforms);
// 	clGetDeviceIDs(f->gpu.platform_id, CL_DEVICE_TYPE_GPU, 1, &f->gpu.device_id, NULL);
// 	f->gpu.context = clCreateContext(NULL, 1, &f->gpu.device_id, NULL, NULL, NULL);
// 	f->gpu.queue = clCreateCommandQueueWithPropertiesAPPLE(f->gpu.context, f->gpu.device_id, 0, NULL);
// 	f->gpu.kernelSource = load_kernel("srcs/mandelbrot.cl");
// 	f->gpu.error = clCreateProgramAndKernelsWithSourceAPPLE(f->gpu.context, 1, &f->gpu.kernelSource, NULL, 1, &f->gpu.device_id, NULL, 1, "mandelbrot_kernel", &f->gpu.programm, &f->gpu.kernel);
}

void	fancy_name_maker(t_fractal *f)
{
	if (!(ft_strncmp(f->name, "-m", 2)))
		f->name = "Mandelbrot";
	else if (!(ft_strncmp(f->name, "-j", 2)))
		f->name = "Julia";
	else if (!(ft_strcmp(f->name, "-b")))
		f->name = "Burning_Ship";
}

void	init_fractal(t_fractal *f)
{
	f->mlx_window = mlx_init(WIDTH, HIGHT, f->name, true);
	if (f->mlx_window == NULL)
		return ;
	f->img.img_ptr = mlx_new_image(f->mlx_window, WIDTH, HIGHT);
	if (f->img.img_ptr == NULL)
		return ;
	mlx_image_to_window(f->mlx_window, f->img.img_ptr, 0, 0);
	data_init(f);
}

void	julia_base_init(t_fractal *f)
{
	f->julia_x = -0.7269;
	f->julia_y = 0.1889;
}

int	mlx_argv_check(int argc, char **argv, t_fractal *f)
{
	if (argc == 1 || argc == 3 || (argc > 2 && (!ft_strcmp(argv[1], "-m")
				|| !ft_strcmp(argv[1], "-b"))))
	{
		info_message();
		return (1);
	}
	if (!(ft_strcmp(argv[1], "-m") == 0 || ft_strcmp(argv[1], "-b") == 0
			|| ft_strcmp(argv[1], "-j") == 0))
	{
		info_message();
		return (1);
	}
	if (!ft_strcmp(argv[1], "-j") && argc == 2)
	{
		ft_printf("no custom values for julia, starting with default values\n");
		julia_base_init(f);
	}
	if (argc > 4 || argc < 2)
	{
		info_message();
		return (1);
	}
	return (0);
}
