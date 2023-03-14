/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvonsovs <fvonsovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 15:12:54 by fvonsovs          #+#    #+#             */
/*   Updated: 2023/03/14 16:51:36 by fvonsovs         ###   ########.fr       */
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
}	t_data;

typedef struct s_map
{
	int	height;
	int	width;
	int	**array;
	int	z_max;
	int	z_min;
}	t_map;

// function definitions
int		you_fucked_up(char *msg);

void	put_pixel(t_data *data, int x, int y, int color);

void	print_controls(t_data *data);

void	render_background(t_data *data, int color, int start_x, int end_x);

int		handle_keypress(int keysym, t_data *data);

void	render(t_data *data);

t_map	*map_init(void);

void	free_map_array(t_map *map);

void	free_split(char **str);

int		get_height(char *filename);

int		count_words(char *str, char c);

int		*parse_line(char *line, t_map *map);

t_map	*parse_map(t_map *map, char *filename);

int		test_map_read(t_map *map);

#endif