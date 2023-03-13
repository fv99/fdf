/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_parse_maps.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvonsovs <fvonsovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 15:52:26 by fvonsovs          #+#    #+#             */
/*   Updated: 2023/03/13 17:53:00 by fvonsovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// initializes map for usage
t_map	*map_init(void)
{
	t_map *map;

	map = (t_map *)malloc(sizeof(t_map));
	if (!map)
		you_fucked_up("Error loading map");
	map->height = 0;
	map->width = 0;
	map->array = NULL;
	map->z_max = 0;
	map->z_min = 0;
	return(map);
}

// will free array of strings created by ft_split
void	free_split(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

// counts the amount of coords in each line of file
int		count_words(char *str, char c)
{
	int i;

	i = 0;
	while(*str)
	{
		if (*str != c)
			++i;
		while (*str && *str != c)
			++str;
	}
	return(i);
}

int	*parse_line(char *line, t_map *map)
{
	int 	*row;
	char	**words;
	int		i;

	words = ft_split(line, ' ');
	row = malloc(sizeof(int) * width);
	if (!row || !words)
	{
		free_split(words);
		you_fucked_up("ft_split or malloc failed in parse_line");
	}
	i = -1;
	while (++i < width)
	{
		row[i] = ft_atoi(words[i]);
		// finish this
	}
	free_split(words);
	return ()
}

t_map	*read_file(t_map *map, char *filename)
{
	int		fd;
	char	*line;
	int		width;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		you_fucked_up("Cannot read from file");
	map = map_init();
	while(line != NULL)
	{
		line = get_next_line(fd);
		map->width = count_words(line, ' ');
		parse_line(line, map, width);
		// to do

	}
	
	
	
	return(map);
}

// test function for map parsing, will print contents of map struct
int	test_map_read(t_map *map, char *filename)
{
	int i, j;

	printf("Height: %d\n", map->height);
	printf("Width: %d\n", map->width);
	printf("Z Max: %d\n", map->z_max);
	printf("Z Min: %d\n", map->z_min);

	printf("Array:\n");
	for (i = 0; i < map->height; i++)
	{
		for (j = 0; j < map->width; j++)
		{
			printf("%d ", map->array[i][j]);
		}
		printf("\n");
	}
}
