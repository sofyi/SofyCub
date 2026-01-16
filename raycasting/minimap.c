/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slamhaou <slamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 23:15:08 by imel-haj          #+#    #+#             */
/*   Updated: 2026/01/16 16:19:19 by slamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	draw_minimap(t_data *data)
{
	int	x;
	int	y;
	int	tile;

	tile = 300//tile = 10 * 10;
		/ (data->map_info.map_w > data->map_info.map_h ? data->map_info.map_w : data->map_info.map_h);//forbidden
	if (tile < 8)
		tile = 8;
	y = 0;
	while (data->map_info.map[y])
	{
		x = 0;
		while (data->map_info.map[y][x])
		{
			draw_square(data, x * tile + 10, y * tile + 10, tile,
				get_minimap_color(data, x, y));
			x++;
		}
		y++;
	}
	draw_square(data, data->player.pos_x * tile + 8, data->player.pos_y * tile
		+ 8, 4, rgb_to_int(255, 0, 0, 255));
}

unsigned int	get_minimap_color(t_data *data, int x, int y)
{
	char	c;

	c = data->map_info.map[y][x];
	if (c == '1')
		return (rgb_to_int(128, 128, 128, 255));
	if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (rgb_to_int(255, 255, 255, 255));
	return (rgb_to_int(0, 0, 0, 255));
}
