/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw_wireframe.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvonsovs <fvonsovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 16:43:16 by fvonsovs          #+#    #+#             */
/*   Updated: 2023/03/20 18:28:04 by fvonsovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
this is how we call bresenham_line in draw_wirefame
technically we shouldnt need this, just call directly with line struct
but i cant be bothered to refactor because of norminette sucking ;)) 
 */
void	draw_line_wrapper(t_data *data, \
		t_2d projection, t_2d prev_projection, int color)
{
	t_line	line;

	line.x1 = prev_projection.x;
	line.y1 = prev_projection.y;
	line.x2 = projection.x;
	line.y2 = projection.y;
	bresenham_line(data, line, color);
}

// wireframe drawing isometric projection
void	draw_wireframe(t_data *data, \
		t_transform_vars v, t_transform *transform, int color)
{
	v.scale = (float)transform->scale;
	v.angle = (float)transform->y_angle + (float)transform->x_angle;
	v.offset.x = transform->x_offset;
	v.offset.y = transform->y_offset;
	v.i = 0;
	while (v.i < data->map->height)
	{
		v.j = 0;
		while (v.j < data->map->width)
		{
			v.point = get_3d_point_from_map(data->map, v.j, v.i);
			v.projection = convert_3d_to_2d(v.point, v.scale, v.angle + (float)transform->z_angle, v.offset);
			if (v.j > 0)
				draw_line_wrapper(data, v.projection, v.prev_projection, color);
			v.prev_projection = v.projection;
			if (v.i > 0)
			{
				v.point_above = get_3d_point_from_map(data->map, v.j, v.i - 1);
				v.projection_above = convert_3d_to_2d(v.point_above, v.scale, v.angle + (float)transform->z_angle, v.offset);
				draw_line_wrapper(data, v.projection, v.projection_above, color);
			}
			v.j++;
		}
		v.i++;
	}
}

// wireframe drawing parallel projection
void	draw_wireframe_parallel(t_data *data, t_transform_vars v, t_transform *transform, int color)
{
	v.scale = (float)transform->scale;
	v.angle = (float)transform->y_angle + (float)transform->x_angle;
	v.offset.x = transform->x_offset;
	v.offset.y = transform->y_offset;
	v.i = 0;
	while (v.i < data->map->height)
	{
		v.j = 0;
		while (v.j < data->map->width)
		{
			v.point = get_3d_point_from_map(data->map, v.j, v.i);
			v.projection = convert_parallel(v.point, v.scale, v.angle + (float)transform->z_angle, v.offset);
			if (v.j > 0)
				draw_line_wrapper(data, v.projection, v.prev_projection, color);
			v.prev_projection = v.projection;
			if (v.i > 0)
			{
				v.point_above = get_3d_point_from_map(data->map, v.j, v.i - 1);
				v.projection_above = convert_parallel(v.point_above, v.scale, v.angle + (float)transform->z_angle, v.offset);
				draw_line_wrapper(data, v.projection, v.projection_above, color);
			}
			v.j++;
		}
		v.i++;
	}
}
