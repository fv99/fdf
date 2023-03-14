/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvonsovs <fvonsovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 16:29:59 by fvonsovs          #+#    #+#             */
/*   Updated: 2023/03/14 16:22:39 by fvonsovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		you_fucked_up(char *msg)
{
	ft_printf("\tERROR: %s\n", msg);
	exit(1);
}

void	put_pixel(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
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
			put_pixel(data, x++, y, color);
		++y;
	}
	// print_controls(data);
}

int		handle_keypress(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
	{
		mlx_destroy_window(data->mlx, data->win);
		data->win = NULL;
	}
	exit (0);
}

void	render(t_data *data)
{
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "Fuck you");
	data->img = mlx_new_image(data->mlx,  WINDOW_WIDTH, WINDOW_HEIGHT);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, &data->line_length,
								&data->endian);
	render_background(data, BACKGROUND_COLOUR, 0, 200);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	mlx_hook(data->win, 2, 1L<<0, handle_keypress, data);
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
		map = read_file(map, argv[1]);
		if (!map)
			you_fucked_up("Error loading map");
		test_map_read(map);
		free(map);
		render(data);
	}
	else
		ft_printf("Usage: %s <[FILE].fdf>\n", argv[0]);
	exit(0);
}

