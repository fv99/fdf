/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvonsovs <fvonsovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 16:29:59 by fvonsovs          #+#    #+#             */
/*   Updated: 2023/03/15 16:06:21 by fvonsovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		you_fucked_up(char *msg)
{
	ft_printf("\tERROR: %s\n", msg);
	exit(1);
}

void	print_controls(t_data *data)
{
	mlx_string_put(data->mlx, data->win, 10, 10, 0xFFFFFF, "controls go here");
}

// will print a vertical strip from start_x to end_x
void	render_background(t_data *data, int color, int start_x, int end_x)
{
	int x;
	int y;

	y = 0;
	while (y < WINDOW_HEIGHT)
	{
		x = start_x;
		while (x < end_x)
			mlx_pixel_put(data->mlx, data->win, x++, y, color);
		++y;
	}
	print_controls(data);
}

int		handle_keypress(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
	{
		mlx_destroy_window(data->mlx, data->win);
		exit (0);
	}
	return(0);
}

// double buffering yo
void	redraw(t_data *data)
{
	char	*temp_addr;
	void	*temp_img;

	print_controls(data);
	test_bresenham_line(data);
	mlx_put_image_to_window(data->mlx, data->win, data->offscreen_img, 0, 0);
	temp_addr = data->addr;
	data->addr = data->offscreen_addr;
	data->offscreen_addr = temp_addr;
	temp_img = data->img;
	data->img = data->offscreen_img;
	data->offscreen_img = temp_img;

    mlx_destroy_image(data->mlx, data->offscreen_img);
    data->offscreen_img = mlx_new_image(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
    data->offscreen_addr = mlx_get_data_addr(data->offscreen_img, &data->bits_per_pixel,
                                              &data->line_length, &data->endian);
}

int	redraw_wrapper(void *param)
{
	t_data *data = (t_data *)param;
	redraw(data);
	return(0);
}

void	render(t_data *data)
{
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "Fuck you");

	data->img = mlx_new_image(data->mlx,  WINDOW_WIDTH, WINDOW_HEIGHT);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, &data->line_length,
									&data->endian);

	data->offscreen_img = mlx_new_image(data->mlx,  WINDOW_WIDTH, WINDOW_HEIGHT);
	data->offscreen_addr = mlx_get_data_addr(data->offscreen_img, &data->bits_per_pixel,
												&data->line_length, &data->endian);
	mlx_hook(data->win, 2, 1L<<0, handle_keypress, data);
	mlx_loop_hook(data->mlx, redraw_wrapper, data);
	mlx_loop(data->mlx);
}

int		main(int argc, char **argv)
{
	t_data	*data;
	t_map	*map;

	if (argc == 2)
	{
		data = malloc(sizeof(t_data));
		map = map_init();
		map = parse_map(map, argv[1]);
		if (!map)
			you_fucked_up("Error loading map");
		test_map_read(map);
		free_map_array(map);
		render(data);
		free(data);
	}
	else
		ft_printf("Usage: %s <[FILE].fdf>\n", argv[0]);
	exit(0);
}
