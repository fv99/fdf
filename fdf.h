/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvonsovs <fvonsovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 15:12:54 by fvonsovs          #+#    #+#             */
/*   Updated: 2023/03/19 17:52:17 by fvonsovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "./libft/libft.h"
# include "./minilibx-linux/mlx.h"
# include <fcntl.h>
# include <errno.h>
# include <math.h>
# include <stdio.h>
# include <unistd.h>
# include <X11/X.h>
# include <X11/keysym.h>

// 4:3 is god's chosen aspect ratio
# define WINDOW_WIDTH 1280
# define WINDOW_HEIGHT 1024

# ifndef M_PI
# define M_PI 3.14159265358979323846
# endif

// map holding struct
typedef struct s_map
{
	int	height;
	int	width;
	int	**array;
	int	z_max;
	int	z_min;
}	t_map;

// struct for transformations
typedef struct s_transform
{
	int	scale;
	int	x_angle;
	int	y_angle;
	int	z_angle;
	int	x_offset;
	int	y_offset;
}	t_transform;

// main data holding struct
typedef struct s_data
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	t_map		*map;
	t_transform	transform;
}	t_data;

// struct for x y z
typedef struct s_3d
{
	int	x;
	int	y;
	int	z;
}	t_3d;

// structs for 2d points and bresenham line increments
typedef struct s_2d
{
	int	x;
	int	y;
}	t_2d;

typedef struct s_increment
{
	int	x;
	int	y;
}	t_increment;

// because norminette sucks
typedef struct s_transform_vars
{
	int		i;
	int		j;
	t_2d	projection;
	t_2d	prev_projection;
	t_2d	offset;
	t_2d	projection_above;
	t_3d	point;
	t_3d	point_above;
	float	angle;
	float	scale;
}			t_transform_vars;


// function definitions
int					you_fucked_up(char *msg);

void				print_controls(t_data *data);

int					render_background(t_data *data, int color, int start_x, int end_x);

int					key_hook(int keysym, t_data *data);

int					render(t_data *data);

t_map				*map_init(void);

void				free_map_array(t_map *map);

void				free_split(char **str);

int					get_height(char *filename);

int					count_words(char *str, char c);

int					*parse_line(char *line, t_map *map);

t_map				*parse_map(t_map *map, char *filename);

t_increment			*calculate_increment(t_increment *inc, int x1, int x2, int y1, int y2);

void				update_error(int *error, int *coord, int error_diff, int coord_diff, int diff);

void				bresenham_line(t_data *data, t_2d p1, t_2d p2, int color);

t_3d				get_3d_point_from_map(t_map *map, int x, int y);

t_2d				convert_3d_to_2d(t_3d p, float scale, float angle, t_2d offset);

t_transform			init_transform();

t_transform_vars	init_transform_vars(t_transform *transform);

void				draw_wireframe(t_data *data, t_transform_vars v, t_transform *transform, int color);

// void	test_bresenham_line(t_data *data);
// int	test_map_read(t_map *map);

#endif