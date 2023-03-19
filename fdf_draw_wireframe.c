/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw_wireframe.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvonsovs <fvonsovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 16:43:16 by fvonsovs          #+#    #+#             */
/*   Updated: 2023/03/19 17:10:01 by fvonsovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// gets 3d point struct at x y from map struct array
t_3d	get_3d_point_from_map(t_map *map, int x, int y)
{
	t_3d	points;

	points.x = x;
	points.y = y;
	points.z = map->array[y][x];
	return(points);
}

/* 
function to convert the 3d points to 2d
uses isometric projection

angle_rad = converts angle in degrees to radians
projection.x calculates x coordinate by 
subtracting the y coordinate of the 3d point from the x coord
multiples the result by the cosine of the angle and the scale factor
adds x offset to position the wireframe on the screen
ditto for projection.y
 */
t_2d	convert_3d_to_2d(t_3d p, float scale, float angle, t_2d offset)
{
	t_2d	projection;
	float	angle_rad;

	angle_rad = angle * M_PI / 180;
	projection.x = (p.x - p.y) * cos(angle_rad) * scale + offset.x;
	projection.y =  (-p.z + (p.x + p.y) * sin(angle_rad)) * scale + offset.y;
	return(projection);
}

t_transform	init_transform()
{
	t_transform transform;

	transform.scale = 50;
	transform.x_angle = 0;
	transform.y_angle = 30;
	transform.z_angle = 0;
	transform.x_offset = WINDOW_WIDTH / 2;
	transform.y_offset = 200;
	return(transform);
}

// wireframe drawing function
void	draw_wireframe(t_data *data, t_map *map, t_transform *transform, int color)
{
	t_transform_vars	v;

	v.scale = (float)transform->scale;
	v.angle = (float)transform->y_angle + (float)transform->x_angle;
	v.offset.x = transform->x_offset;
	v.offset.y = transform->y_offset;
	v.i = 0;
	while (v.i < map->height)
	{
		v.j = 0;
		while (v.j < map->width)
		{
			v.point = get_3d_point_from_map(map, v.j, v.i);
			v.projection = convert_3d_to_2d(v.point, v.scale, v.angle + (float)transform->z_angle, v.offset);
			if (v.j > 0)
				bresenham_line(data, v.projection, v.prev_projection, color);
			v.prev_projection = v.projection;
			if (v.i > 0)
			{
				v.point_above = get_3d_point_from_map(map, v.j, v.i - 1);
				v.projection_above = convert_3d_to_2d(v.point_above, v.scale, v.angle + (float)transform->z_angle, v.offset);
				bresenham_line(data, v.projection, v.projection_above, color);
			}
			v.j++;
		}
		v.i++;
	}
}
