/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_tool.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imel-haj <imel-haj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 15:00:39 by slamhaou          #+#    #+#             */
/*   Updated: 2026/01/17 13:07:23 by imel-haj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

char	*take_lin_data(int fd)
{
	char	*lin;

	lin = NULL;
	while (true)
	{
		free(lin);
		lin = get_next_line(fd);
		if (!lin)
			break ;
		if (lin_is_sps(lin))
			continue ;
		break ;
	}
	return (lin);
}

int	check_zero_player(char *map, int x, char *y_up, char *y_down)
{
	if (map[x - 1] == ' ' || map[x + 1] == ' ' )
		return (1);
	if ((y_down && y_down[x] == ' ') || (y_up && y_up[x] == ' '))
		return (1);
	if (s_w_e_n(map[x]))
	{
		if (map[x - 1] == '1' && map[x + 1] == '1'
			&& y_down && y_down[x] == '1' && y_up && y_up[x] == '1')
			return (1);
	}
	return (0);
}

int	check_first_last_wall(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		if (wall_check(&map[i][0], 'c')
			|| wall_check(&map[i][ft_strlen(map[i]) - 1], 'c'))
			return (1);
		i++;
	}
	return (0);
}

int	check_map(char **map)
{
	int	i;
	int	j;

	if (wall_check(map[0], 's'))
		return (-1);
	if (check_first_last_wall(map))
		return (-1);
	i = 1;
	while (map[i])
	{
		j = 1;
		while (map[i][j])
		{
			if (s_w_e_n(map[i][j]) || map[i][j] == '0')
				if (check_zero_player(map[i], j, map[i - 1], map[i + 1]))
					return (-1);
			j++;
		}
		i++;
	}
	if (wall_check(map[i - 1], 's'))
		return (-1);
	return (0);
}
