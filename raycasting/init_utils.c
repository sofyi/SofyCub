/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slamhaou <slamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 23:16:43 by imel-haj          #+#    #+#             */
/*   Updated: 2026/01/16 16:47:12 by slamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

unsigned int	rgb_to_int(int r, int g, int b, int a)
{
	return ((unsigned int)((r & 0xff) << 24
		| (g & 0xff) << 16 | (b & 0xff) << 8 | (a & 0xff)));
}

static void	set_ns(t_data *data, char c)
{
	if (c == 'N')
	{
		data->player.dir_x = 0;
		data->player.dir_y = -1;
		data->player.plane_x = 0.66;
		data->player.plane_y = 0;
	}
	else if (c == 'S')
	{
		data->player.dir_x = 0;
		data->player.dir_y = 1;
		data->player.plane_x = -0.66;
		data->player.plane_y = 0;
	}
}

static void	set_ew(t_data *data, char c)
{
	if (c == 'E')
	{
		data->player.dir_x = 1;
		data->player.dir_y = 0;
		data->player.plane_x = 0;
		data->player.plane_y = 0.66;
	}
	else if (c == 'W')
	{
		data->player.dir_x = -1;
		data->player.dir_y = 0;
		data->player.plane_x = 0;
		data->player.plane_y = -0.66;
	}
}

void	set_direction(t_data *data, char c)
{
	if (c == 'N' || c == 'S')
		set_ns(data, c);
	else if (c == 'E' || c == 'W')
		set_ew(data, c);
}

void	init_player(t_data *data)
{
	char	**map;
	int		i;
	int		j;

	map = data->map_info.map;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E'
				|| map[i][j] == 'W')
			{
				data->player.pos_x = (double)j + 0.5;
				data->player.pos_y = (double)i + 0.5;
				set_direction(data, map[i][j]);
				return ;
			}
			j++;
		}
		i++;
	}
}
