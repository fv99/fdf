/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw_bresenham_line.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvonsovs <fvonsovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 12:53:09 by fvonsovs          #+#    #+#             */
/*   Updated: 2023/03/19 18:41:29 by fvonsovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// will draw a vertical strip from start_x to end_x
int	render_background(t_data *data, int color, int start_x, int end_x)
{
	int	x;
	int	y;

	y = 0;
	while (y < WINDOW_HEIGHT)
	{
		x = start_x;
		while (x < end_x)
			mlx_pixel_put(data->mlx, data->win, x++, y, color);
		++y;
	}
	print_controls(data);
	return (0);
}

// calculates the direction in which line should be drawn
t_increment	*calculate_increment(t_increment *inc, int x1, int x2, int y1, int y2)
{
	if (x1 < x2)
		inc->x = 1;
	else
		inc->x = -1;
	if (y1 < y2)
		inc->y = 1;
	else
		inc->y = -1;
	return(inc);
}

// error calculation for bresenhams algorithm
void	update_error(int *error, int *coord, int error_diff, int coord_diff, int diff)
{
	if(*error > 0)
	{
		*coord += coord_diff;
		*error -= 2 * diff;
	}
	*error += 2 * error_diff;
}

// draws a line with bresenhams algorithm
// takes two 2d point structs as arguments
void	bresenham_line(t_data *data, t_2d p1, t_2d p2, int color)
{
	t_increment	inc;
	int	dx;
	int	dy;
	int error;
	int	x;
	int	y;

	dx = abs(p2.x - p1.x);
	dy = abs(p2.y - p1.y);
	calculate_increment(&inc, p1.x, p2.x, p1.y, p2.y);
	x = p1.x;
	y = p1.y;
	if (dx > dy)
	{
		error = 2 * dy - dx;
		while (x != p2.x)
		{
			mlx_pixel_put(data->mlx, data->win, x, y, color);
			x += inc.x;
			update_error(&error, &y, dy, inc.y, dx);
		}
	}
	else
	{
		error = 2 * dx - dy;
		while (y != p2.y)
		{
			mlx_pixel_put(data->mlx, data->win, x, y, color);
			y+= inc.y;
			update_error(&error, &x, dx, inc.x, dy);
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
