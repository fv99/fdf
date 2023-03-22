/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvonsovs <fvonsovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 16:32:39 by fvonsovs          #+#    #+#             */
/*   Updated: 2023/03/22 14:31:43 by fvonsovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
	t_intensity	intensity;
	t_color		vars;

	vars.r_base = (base_color >> 16) & 0xFF;
	vars.g_base = (base_color >> 8) & 0xFF;
	vars.b_base = base_color & 0xFF;
	vars.r_whole = (int)(vars.r_base * (1 - weight));
	vars.g_whole = (int)(vars.g_base * (1 - weight));
	vars.b_whole = (int)(vars.b_base * (1 - weight));
	vars.r_fractional = (int)(vars.r_base * weight);
	vars.g_fractional = (int)(vars.g_base * weight);
	vars.b_fractional = (int)(vars.b_base * weight);
	intensity.whole = (vars.r_whole << 16) | (vars.g_whole << 8) | vars.b_whole;
	intensity.fractional = (vars.r_fractional << 16) | \
							(vars.g_fractional << 8) | vars.b_fractional;
	return (intensity);
}

/* 
swaps points
so we always draw from left to right
or from bottom to top
 */
void	swap_points(t_line *line)
{
	int	tmp;

	tmp = line->x1;
	line->x1 = line->x2;
	line->x2 = tmp;
	tmp = line->y1;
	line->y1 = line->y2;
	line->y2 = tmp;
}

// error handling
int	you_fucked_up(char *msg)
{
	ft_printf("\tERROR: %s\n", msg);
	exit(1);
}
