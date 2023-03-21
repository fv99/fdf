/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw_wu_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvonsovs <fvonsovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 15:49:40 by fvonsovs          #+#    #+#             */
/*   Updated: 2023/03/21 16:44:09 by fvonsovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* 
draws horizontal lines with wu's algorithm
calls wu_gradient to get gradient values in x and y directions
calls wu_intensity to get current pixels color intensity

draws pixel closer to ideal line with full intensity
draws pixel 1 pixel below with weaker color intensity
y is incremented by the gradient in the x direction
 */
void	wu_line_horizontal(t_data *data, t_line line, int color)
{
	t_gradient	grad;
	t_intensity	intensity;
	double		x;
	double		y;

	grad = wu_gradient(&line);
	x = line.x1;
	y = line.y1;

	while(x < line.x2)
	{
		intensity = wu_intensity(color, 1 - fabs(y - round(y)));
		mlx_pixel_put(data->mlx, data->win, (int)x, (int)round(y), intensity.whole);
		mlx_pixel_put(data->mlx, data->win, (int)x, (int)round(y) + 1, intensity.fractional);
		x++;
		y += grad.x;
	}
}

// draws vertical lines with wu's algorithm
void	wu_line_vertical(t_data *data, t_line line, int color)
{
	t_gradient	grad;
	t_intensity	intensity;
	double		x;
	double		y;

	grad = wu_gradient(&line);
	x = line.x1;
	y = line.y1;
	while (y < line.y2)
	{
		intensity = wu_intensity(color, 1 - fabs(x - round(x)));
		mlx_pixel_put(data->mlx, data->win, (int)round(y), (int)y, intensity.whole);
		mlx_pixel_put(data->mlx, data->win, (int)round(y) + 1, (int)y, intensity.fractional);
		y++;
		x += grad.y;
	}
}

// draws a line with wu's algorithm
void	wu_line(t_data *data, t_line line, int color)
{
	if (abs(line.y2 - line.y1) < abs(line.x2 - line.x1))
	{
		if (line.x1 > line.x2)
			swap_points(&line);
		wu_line_horizontal(data, line, color);
	}
	else
	{
		if (line.y1 > line.y2)
			swap_points(&line);
		wu_line_vertical(data, line, color);
	}
}
