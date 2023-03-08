/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvonsovs <fvonsovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 16:29:59 by fvonsovs          #+#    #+#             */
/*   Updated: 2023/03/08 14:43:54 by fvonsovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	put_pixel(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	render_background(t_data *img, int color)
{
	int	x;
	int	y;

	x = 0;
	while (x < WINDOW_HEIGHT)
	{
		y = 0;
		while (y < WINDOW_WIDTH)
			put_pixel(img, y++, x, color);
		++x;
	}
}

int	handle_close_keypress(int keysym, t_vars *data)
{
	if (keysym == XK_Escape)
	{
		mlx_destroy_window(data->mlx, data->win);
		data->win = NULL;
	}
	return (0);
}

int	main(void)
{
	t_data	img;
	t_vars	vars;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "Fuck you");
	if (vars.win == NULL || vars.mlx == NULL)
	{
		free(vars.win);
		return (1);
	}
	img.img = mlx_new_image(vars.mlx,  WINDOW_WIDTH, WINDOW_HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	render_background(&img, BACKGROUND_COLOUR);
	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
	mlx_hook(vars.win, 2, 1L<<0, handle_close_keypress, &vars);
	mlx_loop(vars.mlx);
	mlx_destroy_image(vars.mlx, img.img);
	mlx_destroy_display(vars.mlx);
	free(vars.mlx);
}

