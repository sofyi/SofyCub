/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slamhaou <slamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 23:16:13 by imel-haj          #+#    #+#             */
/*   Updated: 2026/01/16 16:30:37 by slamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	raycasting_3d(t_data *data, t_ray ray)
{
	int		x;
	int		line_h;
	int		start;
	int		end;

	x = 0;
	while (x < WIDTH)
	{
		init_ray(data, &ray, x);
		set_ray_step(data, &ray);
		perform_dda(data, &ray);
		if (ray.side >= 2)
			ray.perp_wall_dist = (ray.side_dist_x - ray.delta_dist_x);
		else
			ray.perp_wall_dist = (ray.side_dist_y - ray.delta_dist_y);
		line_h = (int)(HEIGHT / ray.perp_wall_dist);
		start = -line_h / 2 + HEIGHT / 2;
		if (start < 0)
			start = 0;
		end = line_h / 2 + HEIGHT / 2;
		if (end >= HEIGHT)
			end = HEIGHT - 1;
		render_column(data, &ray, x, start, end, line_h);
		x++;
	}
}

void	render_column(t_data *data, t_ray *ray, int x, int start, int end,
		int lineH)
{
	double			wall_x;
	int				tex_x;
	double			step;
	double			tex_pos;
	int				tex_y;
	unsigned char	*p;
	unsigned int	color;

	if (ray->side >= 2)
		wall_x = data->player.pos_y + ray->perp_wall_dist * ray->ray_dir_y;
	else
		wall_x = data->player.pos_x + ray->perp_wall_dist * ray->ray_dir_x;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * (double)data->texture[ray->side].width);
	if (((ray->side >= 2) && ray->ray_dir_x < 0) || ((ray->side < 2)
			&& ray->ray_dir_y > 0))
		tex_x = data->texture[ray->side].width - tex_x - 1;
	step = 1.0 * data->texture[ray->side].height / lineH;
	tex_pos = (start - HEIGHT / 2 + lineH / 2) * step;
	while (start < end)
	{
		tex_y = (int)tex_pos & (data->texture[ray->side].height - 1);
		tex_pos += step;
		p = &data->texture[ray->side].img_ptr->pixels[(tex_y
				* data->texture[ray->side].width + tex_x) * 4];
		color = rgb_to_int(p[0], p[1], p[2], p[3]);
		if (ray->side >= 2)
			color = rgb_to_int(p[0] * 0.7, p[1] * 0.7, p[2] * 0.7, p[3]);
		mlx_put_pixel(data->img, x, start++, color);
	}
}

void	perform_dda(t_data *data, t_ray *ray)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			if (ray->ray_dir_x > 0)
				ray->side = 3;
			else
				ray->side = 2;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			if (ray->ray_dir_y > 0)
				ray->side = 1;
			else
				ray->side = 0;
		}
		if (data->map_info.map[ray->map_y][ray->map_x] == '1')
			hit = 1;
	}
}

void	set_ray_step(t_data *data, t_ray *ray)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (data->player.pos_x - ray->map_x)
			* ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - data->player.pos_x)
			* ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (data->player.pos_y - ray->map_y)
			* ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - data->player.pos_y)
			* ray->delta_dist_y;
	}
}

static double	ft_fabs(double n)
{
	if (n < 0)
	{
		return (-n);
	}
	return (n);
}

void	init_ray(t_data *data, t_ray *ray, int x)
{
	ray->camera_x = 2 * x / (double)WIDTH - 1;
	ray->ray_dir_x = data->player.dir_x + data->player.plane_x * ray->camera_x;
	ray->ray_dir_y = data->player.dir_y + data->player.plane_y * ray->camera_x;
	ray->map_x = (int)data->player.pos_x;
	ray->map_y = (int)data->player.pos_y;
	ray->delta_dist_x = ft_fabs(1 / ray->ray_dir_x);
	if (ray->ray_dir_x == 0)
		ray->delta_dist_x = 1e30;
	ray->delta_dist_y = ft_fabs(1 / ray->ray_dir_y);
	if (ray->ray_dir_y == 0)
		ray->delta_dist_y = 1e30;
}
