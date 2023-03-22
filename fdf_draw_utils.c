/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvonsovs <fvonsovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 18:02:22 by fvonsovs          #+#    #+#             */
/*   Updated: 2023/03/22 14:28:19 by fvonsovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// gets 3d point struct at x y from map struct array
t_3d	xyz_from_map(t_map *map, int x, int y)
{
	t_3d	points;

	points.x = x;
	points.y = y;
	points.z = map->array[y][x];
	return (points);
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
t_2d	_3d_2d(t_3d p, float scale, float angle, t_2d offset)
{
	t_2d	projection;
	float	angle_rad;

	angle_rad = angle * M_PI / 180;
	projection.x = (p.x - p.y) * cos(angle_rad) * scale + offset.x;
	projection.y = (-p.z + (p.x + p.y) * sin(angle_rad)) * scale + offset.y;
	return (projection);
}

// converts 3d points for parallel projection
t_2d	_3d_2d_p(t_3d p, float scale, float angle, t_2d offset)
{
	t_2d	projection;

	projection.x = p.x * scale * cos(angle) + offset.x;
	projection.y = -p.z * scale + p.y * scale * sin(angle) + offset.y;
	return (projection);
}

// initialize our camera struct, keypress changes these
t_transform	init_transform(void)
{
	t_transform	transform;

	transform.scale = 50;
	transform.x_angle = 0;
	transform.y_angle = 30;
	transform.z_angle = 0;
	transform.x_offset = WINDOW_WIDTH / 2;
	transform.y_offset = 200;
	return (transform);
}

// to make draw_wireframe below 25 lines
// declaring of variables used in that function
t_transform_vars	init_transform_vars(t_transform *transform)
{
	t_transform_vars	v;

	v.s = (float)transform->scale;
	v.a = (float)(transform->y_angle + transform->x_angle);
	v.off.x = transform->x_offset;
	v.off.y = transform->y_offset;
	v.i = 0;
	v.j = 0;
	v.prev_proj = (t_2d){0, 0};
	v.p = (t_3d){0, 0, 0};
	v.proj = (t_2d){0, 0};
	v.p_abv = (t_3d){0, 0, 0};
	v.p_a = (t_2d){0, 0};
	return (v);
}
