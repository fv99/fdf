/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvonsovs <fvonsovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 16:32:39 by fvonsovs          #+#    #+#             */
/*   Updated: 2023/03/21 17:16:47 by fvonsovs         ###   ########.fr       */
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

// for initializing the variables for wu's line
void	initialize_wu_vars(t_line *line, t_increment *inc, double *x, double *y)
{
	*x = (double)line->x1;
	*y = (double)line->y1;

	if (line->y2 - line->y1 > 0)
		inc->y = 1;
	else
		inc->y = -1;
	if (line->x2 - line->x1 > 0)
		inc->x = 1;
	else
		inc->x = -1;
}

/* 
calculates gradients for wu's algorithm
grad.x is delta x divided by delta y
grad.x is used for horizontal lines
ditto for grad.y
 */
t_gradient	wu_gradient(t_line *line)
{
	t_gradient	grad;

	grad.x = (double)(line->y2 - line->y1) / (double)(line->x2 - line->x1);
	grad.y = (double)(line->x2 - line->x1) / (double)(line->y2 - line->y1);
	return (grad);
}

/* 
calculates color intensity for wu's algorithm
based on the pixels distance from the ideal line
weight = distance of pixel from ideal line
the closer the distance, higher the weight

we extract the R G B components from the base color
base color = 24 bit integer, first 8 bits are the red component etc.
so we extract the colors by shifting by 8/16 bits

then we calculate the whole and fractional intensities
intensity.whole = color of the pixel closer to the ideal line
intensity.fractional = color that is farther from ideal line
weight * base color = blended line color with background
 */
t_intensity	wu_intensity(int base_color, double weight)
{
    t_intensity intensity;
    int r_base;
    int g_base;
    int b_base;
    int r_whole;
    int g_whole;
    int b_whole;
    int r_fractional;
    int g_fractional;
    int b_fractional;

	r_base = (base_color >> 16) & 0xFF;
	g_base = (base_color >> 8) & 0xFF;
	b_base = base_color & 0xFF;
	r_whole = (int)(r_base * (1 - weight));
	g_whole = (int)(g_base * (1 - weight));
	b_whole = (int)(b_base * (1 - weight));
	r_fractional = (int)(r_base * weight);
	g_fractional = (int)(g_base * weight);
	b_fractional = (int)(b_base * weight);
    intensity.whole = (r_whole << 16) | (g_whole << 8) | b_whole;
    intensity.fractional = (r_fractional << 16) | (g_fractional << 8) | b_fractional;
    return (intensity);
}

/* 
swaps points
so we always draw from left to right
or from bottom to top
 */
void	swap_points(t_line *line)
{
	int tmp;

	tmp = line->x1;
	line->x1 = line->x2;
	line->x2 = tmp;
	tmp = line->y1;
	line->y1 = line->y2;
	line->y2 = tmp;
}