/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imel-haj <imel-haj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 23:16:13 by imel-haj          #+#    #+#             */
/*   Updated: 2026/01/17 16:36:20 by imel-haj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	raycasting_3d(t_data *data)
{
	int		x;
	int		line_h;
	t_ray	ray;

	x = 0;
	while (x < WIDTH)
	{
		init_ray(data, &ray, x);
		set_ray_step(data, &ray);
		perform_dda(data, &ray, 0);
		if (ray.side >= 2)
			ray.perp_wall_dist = (ray.side_dist_x - ray.delta_dist_x);
		else
			ray.perp_wall_dist = (ray.side_dist_y - ray.delta_dist_y);
		line_h = (int)(HEIGHT / ray.perp_wall_dist);
		render_column(data, &ray, x, line_h);
		x++;
	}
}

static void	draw_textured_column(t_data *data, t_ray *ray, t_column *col)
{
	int				tex_y;
	unsigned char	*p;
	unsigned int	color;
	t_img			*tex;

	tex = &data->texture[ray->side];
	while (col->start < col->end)
	{
		tex_y = (int)col->tex_pos & (tex->height - 1);
		col->tex_pos += col->step;
		p = &tex->img_ptr->pixels[(tex_y * tex->width + col->tex_x) * 4];
		color = rgb_to_int(p[0], p[1], p[2], p[3]);
		if (ray->side >= 2)
			color = rgb_to_int(p[0] * 0.7, p[1] * 0.7, p[2] * 0.7, p[3]);
		mlx_put_pixel(data->img, col->x, col->start++, color);
	}
}

static void	prepare_column(t_data *data, t_ray *ray, t_column *col)
{
	double	wall_x;

	col->start = -col->line_h / 2 + HEIGHT / 2;
	if (col->start < 0)
		col->start = 0;
	col->end = col->line_h / 2 + HEIGHT / 2;
	if (col->end >= HEIGHT)
		col->end = HEIGHT - 1;
	if (ray->side >= 2)
		wall_x = data->player.pos_y + ray->perp_wall_dist * ray->ray_dir_y;
	else
		wall_x = data->player.pos_x + ray->perp_wall_dist * ray->ray_dir_x;
	wall_x -= floor(wall_x);
	col->tex_x = (int)(wall_x * (double)data->texture[ray->side].width);
	if (((ray->side >= 2) && ray->ray_dir_x < 0) || ((ray->side < 2)
			&& ray->ray_dir_y > 0))
		col->tex_x = data->texture[ray->side].width - col->tex_x - 1;
	col->step = 1.0 * data->texture[ray->side].height / col->line_h;
	col->tex_pos = (col->start - HEIGHT / 2 + col->line_h / 2) * col->step;
}

void	render_column(t_data *data, t_ray *ray, int x, int line_h)
{
	t_column	col;

	col.x = x;
	col.line_h = line_h;
	prepare_column(data, ray, &col);
	draw_textured_column(data, ray, &col);
}

void	perform_dda(t_data *data, t_ray *ray, int hit)
{
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
