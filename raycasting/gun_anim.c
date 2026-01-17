/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gun_anim.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imel-haj <imel-haj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 23:17:17 by imel-haj          #+#    #+#             */
/*   Updated: 2026/01/10 23:47:32 by imel-haj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	update_animation(t_data *data, double current_time)
{
	if (current_time - data->gun.last_time > 0.1)
	{
		data->gun.frames[data->gun.current_frame]->enabled = false;
		data->gun.current_frame++;
		if (data->gun.current_frame < 5)
			data->gun.frames[data->gun.current_frame]->enabled = true;
		else
		{
			data->gun.is_shooting = false;
			data->gun.current_frame = 0;
			data->gun.frames[0]->enabled = true;
		}
		data->gun.last_time = current_time;
	}
}

void	handle_shooting(void *param)
{
	t_data	*data;
	double	current_time;

	data = (t_data *)param;
	current_time = mlx_get_time();
	if (mlx_is_key_down(data->mlx, MLX_KEY_SPACE) && !data->gun.is_shooting)
	{
		data->gun.is_shooting = true;
		data->gun.current_frame = 0;
		data->gun.last_time = current_time;
	}
	if (data->gun.is_shooting)
		update_animation(data, current_time);
}

void	update_gun_animation(t_data *data)
{
	double	current_time;

	if (!data->gun.is_shooting)
		return ;
	current_time = mlx_get_time();
	if (current_time - data->gun.last_time > 0.1)
	{
		data->gun.frames[data->gun.current_frame]->enabled = false;
		data->gun.current_frame++;
		if (data->gun.current_frame < 5)
		{
			data->gun.frames[data->gun.current_frame]->enabled = true;
		}
		else
		{
			data->gun.is_shooting = false;
			data->gun.current_frame = 0;
			data->gun.frames[0]->enabled = true;
		}
		data->gun.last_time = current_time;
	}
}
