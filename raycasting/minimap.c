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

static void	render_tile(t_data *data, t_mmap m, int x, int y)
{
	t_point	p;

	if (y >= 0 && y < data->map_info.map_h && x >= 0
		&& x < data->map_info.map_w)
	{
		p.x = (x - m.start_x) * m.tile + 10;
		p.y = (y - m.start_y) * m.tile + 10;
		draw_square(data, p, m.tile, get_minimap_color(data, x, y));
	}
}

void	draw_minimap(t_data *data)
{
	t_mmap	m;
	t_point	p;

	m.radius = 4;
	m.tile = 15;
	m.start_y = (int)data->player.pos_y - m.radius;
	m.start_x = (int)data->player.pos_x - m.radius;
	m.y = m.start_y;
	while (m.y <= m.start_y + (m.radius * 2))
	{
		m.x = m.start_x;
		while (m.x <= m.start_x + (m.radius * 2))
		{
			render_tile(data, m, m.x, m.y);
			m.x++;
		}
		m.y++;
	}
	p.x = (m.radius * m.tile) + 10 + (m.tile / 3);
	p.y = (m.radius * m.tile) + 10 + (m.tile / 3);
	draw_square(data, p, m.tile / 3, rgb_to_int(255, 0, 0, 255));
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
