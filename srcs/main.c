/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 12:16:06 by ldick             #+#    #+#             */
/*   Updated: 2025/03/23 21:20:20 by ldick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

// int	main(int argc, char *argv[])
// {
// 	t_fractal	f;

// 	f.name = argv[1];
// 	if (mlx_argv_check(argc, argv, &f) == 1)
// 		return (1);
// 	if (argc == 4 && !ft_strcmp(argv[1], "-j"))
// 	{
// 		f.julia_x = atodbl(argv[2]);
// 		f.julia_y = atodbl(argv[3]);
// 	}
	
// 	fancy_name_maker(&f);
// 	init_fractal(&f);
// 	int	widht = 800;
// 	int	height = 600;
// 	int	*image = (int*)malloc(sizeof(int) * widht * height);
// 	f.gpu.image_buffer = clCreateBuffer(f.gpu.context, CL_MEM_WRITE_ONLY, sizeof(int) * widht * height, NULL, NULL);
// 	clSetKernelArg(f.gpu.kernel, 0, sizeof(cl_mem), &f.gpu.image_buffer);
// 	clSetKernelArg(f.gpu.kernel, 1, sizeof(int), &widht);
// 	clSetKernelArg(f.gpu.kernel, 2, sizeof(int), &height);
// 	clSetKernelArg(f.gpu.kernel, 3, sizeof(float), &f.zoom);
// 	clSetKernelArg(f.gpu.kernel, 4, sizeof(float), &f.shift_x);
// 	clSetKernelArg(f.gpu.kernel, 5, sizeof(float), &f.shift_y);
// 	clSetKernelArg(f.gpu.kernel, 6, sizeof(int), &f.max_iterations);
// 	clSetKernelArg(f.gpu.kernel, 7, sizeof(float), &f.escape_val);
// 	size_t	global_work_size[] = { widht, height};
// 	clEnqueueNDRangeKernel(f.gpu.queue, f.gpu.kernel, 2, NULL, global_work_size, NULL, 0, NULL, NULL);
// 	clEnqueueReadBuffer(f.gpu.queue, f.gpu.image_buffer, CL_TRUE, 0, sizeof(int) * widht * height, f.gpu.image_buffer, 0, NULL, NULL);
	
// 	fractal_render(&f);
// 	mlx_key_hook(f.mlx_window, my_key_handler, &f);
// 	mlx_scroll_hook(f.mlx_window, my_scroll_func, &f);
// 	mlx_loop(f.mlx_window);
// 	mlx_terminate(f.mlx_window);
// 	return (0);
// }

int main() {
    // Initialize GLFW and create a window
    if (!glfwInit()) return -1;
    GLFWwindow* window = glfwCreateWindow(800, 600, "Mandelbrot", NULL, NULL);
    glfwMakeContextCurrent(window);

    // Initialize GLEW
    glewInit();

    // Initialize MLX42
    mlx_t* mlx = mlx_init(800, 600, "Mandelbrot", true);
    if (!mlx) return -1;

    // Create an OpenGL texture
    GLuint tex;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 800, 600, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    glBindTexture(GL_TEXTURE_2D, 0);

    // Create OpenCL context and command queue
    cl_device_id device;
    cl_context context = createCLGLContext(&device);
    cl_command_queue queue = clCreateCommandQueue(context, device, 0, NULL);

    // Create OpenCL image from OpenGL texture
    cl_int err;
    cl_mem clImage = clCreateFromGLTexture(context, CL_MEM_WRITE_ONLY, GL_TEXTURE_2D, 0, tex, &err);
    // Error handling...

    // Build and set up OpenCL kernel
    // ...

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        // Acquire OpenGL texture for OpenCL
        clEnqueueAcquireGLObjects(queue, 1, &clImage, 0, NULL, NULL);

        // Execute OpenCL kernel
        // ...

        // Release OpenGL texture from OpenCL
        clEnqueueReleaseGLObjects(queue, 1, &clImage, 0, NULL, NULL);
        clFinish(queue);

        // Render with MLX42
        mlx_image_t* img = mlx_new_image(mlx, 800, 600);
        mlx_texture_t* texture = mlx_load_texture_from_opengl(mlx, tex);
        mlx_draw_texture(img, texture, 0, 0);
        mlx_image_to_window(mlx, img, 0, 0);
        mlx_delete_texture(texture);
        mlx_delete_image(mlx, img);

        // Swap buffers and poll events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Cleanup
    clReleaseMemObject(clImage);
    clReleaseCommandQueue(queue);
    clReleaseContext(context);
    glDeleteTextures(1, &tex);
    mlx_terminate(mlx);
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}