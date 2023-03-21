/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvonsovs <fvonsovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 16:29:59 by fvonsovs          #+#    #+#             */
/*   Updated: 2023/03/21 17:07:44 by fvonsovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	you_fucked_up(char *msg)
{
	ft_printf("\tERROR: %s\n", msg);
	exit(1);
}

int	handle_destroy_notify(t_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	exit(0);
}

void	print_controls(t_data *data)
{
	mlx_string_put(data->mlx, data->win, 10, 10, 0xFFFFFF, "Controls:");
	mlx_string_put(data->mlx, data->win, 10, 30, 0xFFFFFF, "[WASD]  Movement");
	mlx_string_put(data->mlx, data->win, 10, 45, 0xFFFFFF, "[Q/E]   Rotate");
	mlx_string_put(data->mlx, data->win, 10, 60, 0xFFFFFF, "[+/-]   Zoom");
	mlx_string_put(data->mlx, data->win, 10, 75, 0xFFFFFF, \
	"[P]     Switch projection");
		mlx_string_put(data->mlx, data->win, 10, 90, 0xFFFFFF, \
	"[L]     Anti-aliasing ON/OFF");
	mlx_string_put(data->mlx, data->win, 10, 115, 0xFFFFFF, "[ESC]   Exit");
	if (data->project == 0)
		mlx_string_put(data->mlx, data->win, 1150, 10, 0xFFFFFF, \
		"Projection: Isometric");
	else
		mlx_string_put(data->mlx, data->win, 1150, 10, 0xFFFFFF, \
		"Projection: Parallel");
	if (data->wu_tang == 0)
		mlx_string_put(data->mlx, data->win, 1150, 25, 0xFFFFFF, \
		"Anti-aliasing: [OFF]");
	else
		mlx_string_put(data->mlx, data->win, 1150, 25, 0xFFFFFF, \
		"Anti-aliasing: [ON]");
}

int	handle_keypress(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
		handle_destroy_notify(data);
	else if (keysym == XK_w || keysym == XK_W)
		data->transform.y_offset -= 10;
	else if (keysym == XK_s || keysym == XK_S)
		data->transform.y_offset += 10;
	else if (keysym == XK_a || keysym == XK_A)
		data->transform.x_offset -= 10;
	else if (keysym == XK_d || keysym == XK_D)
		data->transform.x_offset += 10;
	else if (keysym == XK_plus || keysym == XK_KP_Add)
		data->transform.scale += 5;
	else if (keysym == XK_minus || keysym == XK_KP_Subtract)
		data->transform.scale -= 5;
	else if (keysym == XK_q || keysym == XK_Q)
		data->transform.z_angle += 2;
	else if (keysym == XK_e || keysym == XK_E)
		data->transform.z_angle -= 2;
	else if (keysym == XK_p || keysym == XK_P)
		data->project = !data->project;
	else if (keysym == XK_l || keysym == XK_L)
		data->wu_tang = !data->wu_tang;
	return (render_background(data, 0x000000, 0, WINDOW_WIDTH));
}

int	render(t_data *data)
{
	t_transform_vars	v;

	v = init_transform_vars(&data->transform);
	if (data->win != NULL)
	{
		if (data->project == 0)
			draw_wireframe(data, v, &data->transform, 0xFFFFFF);
		else if (data->project != 0)
			draw_wireframe_parallel(data, v, &data->transform, 0xFFFFFF);
		print_controls(data);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;
	t_map	*map;

	if (argc == 2)
	{
		map = map_init();
		map = parse_map(map, argv[1]);
		if (!map)
			you_fucked_up("Error loading map");
		data.transform = init_transform();
		data.map = map;
		data.mlx = mlx_init();
		data.win = mlx_new_window(data.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "FdF");
		mlx_loop_hook(data.mlx, &render, &data);
		mlx_hook(data.win, 17, 1L << 17, handle_destroy_notify, &data);
		mlx_hook(data.win, 2, 1L << 0, handle_keypress, &data);
		mlx_loop(data.mlx);
		mlx_destroy_display(data.mlx);
		free_map_array(map);
		free(data.mlx);
	}
	else
		ft_printf("Usage: %s <[FILE].fdf>\n", argv[0]);
	exit(0);
}
