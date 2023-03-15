/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvonsovs <fvonsovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 15:12:54 by fvonsovs          #+#    #+#             */
/*   Updated: 2023/03/15 14:13:40 by fvonsovs         ###   ########.fr       */
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
#include <X11/X.h>
#include <X11/keysym.h>

// 4:3 is god's chosen aspect ratio
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 1024

// colours
#define BACKGROUND_COLOUR 0x2a2a2a

// structs
typedef struct	s_data {
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	void	*offscreen_img;
	char	*offscreen_addr;
}	t_data;

typedef struct s_map
{
	int	height;
	int	width;
	int	**array;
	int	z_max;
	int	z_min;
}	t_map;

typedef struct s_2d
{
	int x;
	int y;
}	t_2d;

typedef struct s_increment
{
	int x;
	int y;
}	t_increment;

// function definitions
int		you_fucked_up(char *msg);

void	print_controls(t_data *data);

void	render_background(t_data *data, int color, int start_x, int end_x);

int		handle_keypress(int keysym, t_data *data);

void	redraw(t_data *data);

void	render(t_data *data);

t_map	*map_init(void);

void	free_map_array(t_map *map);

void	free_split(char **str);

int		get_height(char *filename);

int		count_words(char *str, char c);

int		*parse_line(char *line, t_map *map);

t_map	*parse_map(t_map *map, char *filename);

int		test_map_read(t_map *map);

t_increment	*calculate_increment(t_increment *inc, int x1, int x2, int y1, int y2);

void	update_error(int *error, int *coord, int error_diff, int coord_diff, int diff);

void	bresenham_line(t_data *data, t_2d p1, t_2d p2, int color);

void	test_bresenham_line(t_data *data);

#endif