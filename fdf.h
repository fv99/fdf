/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvonsovs <fvonsovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 15:12:54 by fvonsovs          #+#    #+#             */
/*   Updated: 2023/03/22 14:27:45 by fvonsovs         ###   ########.fr       */
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
#  define M_PI 3.14159265358979323846
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

// struct for transformations (camera etc.)
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
	int			project;
	int			wu_tang;
	t_map		*map;
	t_transform	transform;
}	t_data;

// color holding struct for wu's line alg
typedef struct s_color
{
	int	r_base;
	int	g_base;
	int	b_base;
	int	r_whole;
	int	g_whole;
	int	b_whole;
	int	r_fractional;
	int	g_fractional;
	int	b_fractional;
}	t_color;

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

// i forgot why we have the same struct twice
typedef struct s_increment
{
	int	x;
	int	y;
}	t_increment;

// gradient and intensity structs for wu's line algorithm
typedef struct s_gradient
{
	double	x;
	double	y;
}	t_gradient;

typedef struct s_intensity
{
	int	whole;
	int	fractional;
}	t_intensity;

// because norminette sucks
typedef struct s_transform_vars
{
	int		i;
	int		j;
	t_2d	proj;
	t_2d	prev_proj;
	t_2d	off;
	t_2d	p_a;
	t_3d	p;
	t_3d	p_abv;
	float	a;
	float	s;
}			t_transform_vars;

// line holding struct
typedef struct s_line
{
	int			x1;
	int			x2;
	int			y1;
	int			y2;
	int			dx;
	int			dy;
	t_increment	inc;
	int			error;
}	t_line;

//			fdf.c

int					handle_destroy_notify(t_data *data);

void				print_controls(t_data *data);

int					handle_keypress(int keysym, t_data *data);

int					render(t_data *data);

//			fdf_map_utils.c

// int				test_map_read(t_map *map);

t_map				*map_init(void);

void				free_map_array(t_map *map);

void				free_split(char **str);

//			fdf_map_parser.c

int					get_height(char *filename);

int					count_words(char *str, char c);

int					*parse_line(char *line, t_map *map);

t_map				*parse_map(t_map *map, char *filename);

//			fdf_draw_utils.c

t_3d				xyz_from_map(t_map *map, int x, int y);

t_2d				_3d_2d(t_3d p, float scale, float angle, t_2d offset);

t_2d				_3d_2d_p(t_3d p, float scale, float angle, t_2d offset);

t_transform			init_transform(void);

t_transform_vars	init_transform_vars(t_transform *transform);

//			fdf_draw_utils_2.c

void				initialize_wu_vars(t_line *line, \
						t_increment *inc, double *x, double *y);

t_gradient			wu_gradient(t_line *line);

t_intensity			wu_intensity(int base_color, double weight);

void				swap_points(t_line *line);

int					you_fucked_up(char *msg);

//			fdf_draw_bresenham_line.c

t_increment			calculate_increment(t_line *line);

void				update_error(t_line *line, int *coord, \
						int error_diff, int coord_diff);

void				initialize_line_vars(t_line *line, \
						t_increment *inc, int *x, int *y);

void				bresenham_line(t_data *data, t_line line, int color);

// void				test_bresenham_line(t_data *data);

//			fdf_draw_wu_line.c

void				wu_line_horizontal(t_data *data, t_line line, int color);

void				wu_line_vertical(t_data *data, t_line line, int color);

void				wu_line(t_data *data, t_line line, int color);

//			fdf_draw_wireframe.c

int					render_background(t_data *data, int color, \
						int start_x, int end_x);

void				draw_line_wrapper(t_data *data, t_2d projection, \
						t_2d prev_projection, int color);

void				draw_wireframe(t_data *data, t_transform_vars v, \
						t_transform *transform, int color);

void				draw_wireframe_parallel(t_data *data, t_transform_vars v, \
						t_transform *transform, int color);

#endif