/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slamhaou <slamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 23:15:59 by imel-haj          #+#    #+#             */
/*   Updated: 2026/01/17 17:33:18 by slamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	rotate_player(t_data *data, double angle)
{
	double	old_dirx;
	double	old_planex;

	old_dirx = data->player.dir_x;
	data->player.dir_x = data->player.dir_x * cos(angle) - data->player.dir_y
		* sin(angle);
	data->player.dir_y = old_dirx * sin(angle) + data->player.dir_y
		* cos(angle);
	old_planex = data->player.plane_x;
	data->player.plane_x = data->player.plane_x * cos(angle)
		- data->player.plane_y * sin(angle);
	data->player.plane_y = old_planex * sin(angle) + data->player.plane_y
		* cos(angle);
}

void	move_player(t_data *data, double dx, double dy)
{
	double	nx;
	double	ny;
	double	bx;
	double	by;

	nx = data->player.pos_x + dx;
	ny = data->player.pos_y + dy;
	bx = 0.2;
	if (dx < 0)
		bx = -0.2;
	by = 0.2;
	if (dy < 0)
		by = -0.2;
	if (data->map_info.map[(int)(ny + by)][(int)(nx + bx)] != '1')
	{
		data->player.pos_x = nx;
		data->player.pos_y = ny;
	}
}

void	handle_input(void *param)
{
	t_data	*d;
	double	s;

	d = (t_data *)param;
	s = 0.08;
	if (mlx_is_key_down(d->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(d->mlx);
	if (mlx_is_key_down(d->mlx, MLX_KEY_W))
		move_player(d, d->player.dir_x * s, d->player.dir_y * s);
	if (mlx_is_key_down(d->mlx, MLX_KEY_S))
		move_player(d, -d->player.dir_x * s, -d->player.dir_y * s);
	if (mlx_is_key_down(d->mlx, MLX_KEY_A))
		move_player(d, d->player.dir_y * s, -d->player.dir_x * s);
	if (mlx_is_key_down(d->mlx, MLX_KEY_D))
		move_player(d, -d->player.dir_y * s, d->player.dir_x * s);
	if (mlx_is_key_down(d->mlx, MLX_KEY_RIGHT))
		rotate_player(d, 0.05);
	if (mlx_is_key_down(d->mlx, MLX_KEY_LEFT))
		rotate_player(d, -0.05);
}

void	mouse_hook(double xpos, double ypos, void *param)
{
	t_data			*data;
	static double	old_x = WIDTH / 2;
	double			delta_x;

	data = (t_data *)param;
	(void)ypos;
	delta_x = xpos - old_x;
	if (delta_x != 0)
		rotate_player(data, delta_x * 0.002);
	old_x = xpos;
}
