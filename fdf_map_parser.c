/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_map_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvonsovs <fvonsovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 15:52:26 by fvonsovs          #+#    #+#             */
/*   Updated: 2023/03/14 16:51:23 by fvonsovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// finds the height of our map based on amount of lines
int		get_height(char *filename)
{
	int		fd; 
	int		height;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		you_fucked_up("Cannot read from file in get_height");
	height = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		free(line);
		line = get_next_line(fd);
		height++;
	}
	free(line);
	close(fd);
	return(height);
}

// counts the amount of coords in each line of file
int		count_words(char *str, char c)
{
	int i;

	i = 0;
	if (!str || *str == '\0')
        return (0);
	while(*str)
	{
		if (*str != c)
		{
			++i;
			while (*str && *str != c)
				++str;
		}
		else
			str++;
	}
	return(i);
}

// parses line to find value of each point
int	*parse_line(char *line, t_map *map)
{
	int 	*row;
	char	**words;
	int		i;

	words = ft_split(line, ' ');
	row = malloc(sizeof(int) * map->width);
	if (!row || !words)
	{
		free_split(words);
		you_fucked_up("ft_split or malloc failed in parse_line");
	}
	i = -1;
	while (++i < map->width)
	{
		row[i] = ft_atoi(words[i]);
		if (row[i] > map->z_max)
			map->z_max = row[i];
		if (row[i] < map->z_min)
			map->z_min = row[i];
	}
	free_split(words);
	return (row);
}

// returns a map struct with array storing X-Y-Z values from file
t_map	*parse_map(t_map *map, char *filename)
{
	int		fd;
	char	*line;
	int		i;

	i = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		you_fucked_up("Cannot read from file in read_file");
	line = get_next_line(fd);
	map->height = get_height(filename);
	map->width = count_words(line, ' ');
	map->array = malloc(sizeof(int **) * map->height);
	if (!map->array)
        you_fucked_up("Allocation failed in read_file");
	while(line != NULL)
	{
		map->array[i] = parse_line(line, map);
		free(line);
		i++;
		line = get_next_line(fd);
	}
	close(fd);
	return(map);
}
