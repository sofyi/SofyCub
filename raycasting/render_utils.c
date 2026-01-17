/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slamhaou <slamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 23:16:27 by imel-haj          #+#    #+#             */
/*   Updated: 2026/01/16 16:35:20 by slamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	draw_ceiling_floor(t_data *data)
{
	int				x;
	int				y;
	unsigned int	c_color;
	unsigned int	f_color;

	c_color = rgb_to_int(data->clr[0][1], data->clr[0][2], data->clr[0][3], 0);
	f_color = rgb_to_int(data->clr[1][1], data->clr[1][2], data->clr[1][3],
			255);
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			if (y < HEIGHT / 2)
				mlx_put_pixel(data->img, x, y, c_color);
			else
				mlx_put_pixel(data->img, x, y, f_color);
			x++;
		}
		y++;
	}
}

void	draw_square(t_data *data, t_point p, int size, uint32_t color)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			if (p.x + j < WIDTH && p.y + i < HEIGHT)
				mlx_put_pixel(data->img, p.x + j, p.y + i, color);
			j++;
		}
		i++;
	}
}
