/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw_wireframe.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvonsovs <fvonsovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 16:43:16 by fvonsovs          #+#    #+#             */
/*   Updated: 2023/03/16 18:01:36 by fvonsovs         ###   ########.fr       */
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

// wireframe drawing function
void	draw_wireframe(t_data *data, t_map *map, int color)
{
	int		i;
	int		j;
	t_2d 	projection;
	t_2d	prev_projection;
	t_2d	offset;
	t_2d	projection_above;
	t_3d	point;
	t_3d	point_above;
	float	angle;
	float	scale;

	scale = 50.0;
	angle = 45.0;
	offset.x = WINDOW_WIDTH / 2;
	offset.y = 200;
	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			point = get_3d_point_from_map(map, j, i);
			projection = convert_3d_to_2d(point, scale, angle, offset);
			if (j > 0)
				bresenham_line(data, projection, prev_projection, color);
			prev_projection = projection;
			if (i > 0)
			{
				point_above = get_3d_point_from_map(map, j, i - 1);
				projection_above = convert_3d_to_2d(point_above, scale, angle, offset);
				bresenham_line(data, projection, projection_above, color);
			}
			j++;
		}
		i++;
	}
}
