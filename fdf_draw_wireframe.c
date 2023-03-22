/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw_wireframe.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvonsovs <fvonsovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 16:43:16 by fvonsovs          #+#    #+#             */
/*   Updated: 2023/03/22 14:28:18 by fvonsovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
this is how we call bresenham_line in draw_wirefame
technically we shouldnt need this, just call directly with line struct
but i cant be bothered to refactor because of bs 4 argument limit ;)) 
 */
void	draw_line_wrapper(t_data *data, \
		t_2d proj, t_2d prev_proj, int color)
{
	t_line	line;

	line.x1 = prev_proj.x;
	line.y1 = prev_proj.y;
	line.x2 = proj.x;
	line.y2 = proj.y;
	if (data->wu_tang == 0)
		bresenham_line(data, line, color);
	else
		wu_line(data, line, color);
}

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

/* 
wireframe drawing isometric projection

i wonder, what should we name our variables?
should it be something easily understandable?
like offset, scale, angle etc?

or should it be some unreadable bullshit because
we have an arbitrary 80 column wide limit?

s = scale
a = angle
off = offset
p_abv = point_above
proj = projection
p_a = projection above
prev_proj = previous projection
 */
void	draw_wireframe(t_data *data, \
		t_transform_vars v, t_transform *t, int color)
{
	v.s = (float)t->scale;
	v.a = (float)t->y_angle + (float)t->x_angle;
	v.off.x = t->x_offset;
	v.off.y = t->y_offset;
	v.i = 0;
	while (v.i < data->map->height)
	{
		v.j = 0;
		while (v.j < data->map->width)
		{
			v.p = xyz_from_map(data->map, v.j, v.i);
			v.proj = _3d_2d(v.p, v.s, v.a + (float)t->z_angle, v.off);
			if (v.j > 0)
				draw_line_wrapper(data, v.proj, v.prev_proj, color);
			v.prev_proj = v.proj;
			if (v.i > 0)
			{
				v.p_abv = xyz_from_map(data->map, v.j, v.i - 1);
				v.p_a = _3d_2d(v.p_abv, v.s, v.a + (float)t->z_angle, v.off);
				draw_line_wrapper(data, v.proj, v.p_a, color);
			}
			v.j++;
		}
		v.i++;
	}
}

// wireframe drawing parallel proj
void	draw_wireframe_parallel(t_data *data, \
		t_transform_vars v, t_transform *t, int color)
{
	v.s = (float)t->scale;
	v.a = (float)t->y_angle + (float)t->x_angle;
	v.off.x = t->x_offset;
	v.off.y = t->y_offset;
	v.i = 0;
	while (v.i < data->map->height)
	{
		v.j = 0;
		while (v.j < data->map->width)
		{
			v.p = xyz_from_map(data->map, v.j, v.i);
			v.proj = _3d_2d_p(v.p, v.s, v.a + (float)t->z_angle, v.off);
			if (v.j > 0)
				draw_line_wrapper(data, v.proj, v.prev_proj, color);
			v.prev_proj = v.proj;
			if (v.i > 0)
			{
				v.p_abv = xyz_from_map(data->map, v.j, v.i - 1);
				v.p_a = _3d_2d_p(v.p_abv, v.s, v.a + (float)t->z_angle, v.off);
				draw_line_wrapper(data, v.proj, v.p_a, color);
			}
			v.j++;
		}
		v.i++;
	}
}
