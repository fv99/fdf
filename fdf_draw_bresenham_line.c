/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw_bresenham_line.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvonsovs <fvonsovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 12:53:09 by fvonsovs          #+#    #+#             */
/*   Updated: 2023/03/21 16:40:12 by fvonsovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// calculates the direction in which line should be drawn
t_increment	calculate_increment(t_line *line)
{
	t_increment	inc;

	if (line->x1 < line->x2)
		inc.x = 1;
	else
		inc.x = -1;
	if (line->y1 < line->y2)
		inc.y = 1;
	else
		inc.y = -1;
	return (inc);
}

// error calculation for bresenhams algorithm
void	update_error(t_line *line, int *coord, int error_diff, int coord_diff)
{
	int	diff;

	if (line->dx > line->dy)
		diff = line->dx;
	else
		diff = line->dy;
	if (line->error > 0)
	{
		*coord += coord_diff;
		line->error -= 2 * diff;
	}
	line->error += 2 * error_diff;
}

// another one because 25 lines is too much for 42 :))
void	initialize_line_vars(t_line *line, t_increment *inc, int *x, int *y)
{
	line->dx = abs(line->x2 - line->x1);
	line->dy = abs(line->y2 - line->y1);
	inc->x = 0;
	inc->y = 0;
	*inc = calculate_increment(line);
	*x = line->x1;
	*y = line->y1;
	line->error = line->dx - line->dy;
}

// draws a line with bresenhams algorithm
// called by draw_line_wrapper function
void	bresenham_line(t_data *data, t_line line, int color)
{
	t_increment	inc;
	int			x;
	int			y;

	initialize_line_vars(&line, &inc, &x, &y);
	if (line.dx > line.dy)
	{
		line.error = 2 * line.dy - line.dx;
		while (x != line.x2)
		{
			mlx_pixel_put(data->mlx, data->win, x, y, color);
			x += inc.x;
			update_error(&line, &y, line.dy, inc.y);
		}
	}
	else
	{
		line.error = 2 * line.dx - line.dy;
		while (y != line.y2)
		{
			mlx_pixel_put(data->mlx, data->win, x, y, color);
			y += inc.y;
			update_error(&line, &x, line.dx, inc.x);
		}
	}
}

/* 
// test function
void	test_bresenham_line(t_data *data)
{
	t_2d p1, p2;

	p1.x = 300;
	p1.y = 300;
	p2.x = 500;
	p2.y = 200;
	bresenham_line (data, p1, p2, 0xFFFFFF);

	p1.x = 500;
	p1.y = 500;
	p2.x = 400;
	p2.y = 300;
	bresenham_line (data, p1, p2, 0xFFFFFF);

	p1.x = 900;
	p1.y = 500;
	p2.x = 200;
	p2.y = 400;
	bresenham_line (data, p1, p2, 0xFFFFFF);

	p1.x = 200;
	p1.y = 500;
	p2.x = 200;
	p2.y = 450;
	bresenham_line (data, p1, p2, 0xFFFFFF);	
}
 */
