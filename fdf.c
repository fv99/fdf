/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvonsovs <fvonsovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 16:29:59 by fvonsovs          #+#    #+#             */
/*   Updated: 2023/03/19 17:00:27 by fvonsovs         ###   ########.fr       */
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
	mlx_string_put(data->mlx, data->win, 10, 10, 0xFFFFFF, "Controls:");
	mlx_string_put(data->mlx, data->win, 10, 30, 0xFFFFFF, "[WASD]  Move Camera");
	mlx_string_put(data->mlx, data->win, 10, 45, 0xFFFFFF, "[Q/E]   Rotate");
	mlx_string_put(data->mlx, data->win, 10, 60, 0xFFFFFF, "[+/-]   Zoom");
	mlx_string_put(data->mlx, data->win, 10, 75, 0xFFFFFF, "[ESC]   Exit");
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
	t_transform *transform;

	transform = &data->transform;
	if (keysym == XK_Escape)
	{
		mlx_destroy_window(data->mlx, data->win);
		exit (0);
	}
	else if (keysym == XK_w || keysym == XK_W)
		transform->y_offset -= 10;
	else if (keysym == XK_s || keysym == XK_S)
		transform->y_offset += 10;
	else if (keysym == XK_a || keysym == XK_A)
		transform->x_offset -= 10;
	else if (keysym == XK_d || keysym == XK_D)
		transform->x_offset += 10;
	else if (keysym == XK_plus || keysym == XK_KP_Add)
		transform->scale += 5;
	else if (keysym == XK_minus || keysym == XK_KP_Subtract)
		transform->scale -= 5;
	else if (keysym == XK_q || keysym == XK_Q)
		transform->z_angle += 2;
	else if (keysym == XK_e || keysym == XK_E)
		transform->z_angle -= 2;
	render_background(data, 0x000000, 0, WINDOW_WIDTH);
	return(0);
}

int		render(t_data *data)
{
	if (data->win != NULL)
	{
		draw_wireframe(data, data->map, &data->transform, 0xFFFFFF);
		print_controls(data);
	}
	return (0);
}

int		main(int argc, char **argv)
{
	t_data	data;
	t_map	*map;

	if (argc == 2)
	{
		map = map_init();
		map = parse_map(map, argv[1]);
		if (!map)
			you_fucked_up("Error loading map");
		test_map_read(map);
		data.transform = init_transform();
		data.map = map;
		data.mlx = mlx_init();
		data.win = mlx_new_window(data.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "Fuck you");
		mlx_loop_hook(data.mlx, &render, &data);
		mlx_hook(data.win, 2, 1L<<0, handle_keypress, &data);
		mlx_loop(data.mlx);
		mlx_destroy_display(data.mlx);
		free_map_array(map);
		free(data.mlx);
	}
	else
		ft_printf("Usage: %s <[FILE].fdf>\n", argv[0]);
	exit(0);
}
