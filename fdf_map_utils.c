/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_map_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvonsovs <fvonsovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 16:44:13 by fvonsovs          #+#    #+#             */
/*   Updated: 2023/03/19 17:44:04 by fvonsovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* 
// test function, will print contents of map array
int test_map_read(t_map *map)
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
			printf("%i ", map->array[i][j]);
		}
		printf("\n");
	}
	return (0);
}
 */

// initializes map for usage
t_map	*map_init(void)
{
	t_map	*map;

	map = (t_map *)malloc(sizeof(t_map));
	if (!map)
		you_fucked_up("Error allocating map in map_init");
	map->height = 0;
	map->width = 0;
	map->array = NULL;
	map->z_max = 0;
	map->z_min = 0;
	return(map);
}

// does exactly what its called
void	free_map_array(t_map *map)
{
	int i;

	i = 0;
	while (i < map->height)
	{
		free(map->array[i]);
		i++;
	}
	free(map->array);
	map->array = NULL;
	map->height = 0;
	map->width = 0;
	map->z_max = 0;
	map->z_min = 0;
	free(map);
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
