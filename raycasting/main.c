/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slamhaou <slamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 15:50:35 by imel-haj          #+#    #+#             */
/*   Updated: 2026/01/16 16:43:13 by slamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

// void	my_mlx_pixel_put(mlx_image_t *img, int x, int y, unsigned int color)
// {
// 	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
// 		return ;
// 	mlx_put_pixel(img, x, y, color);
// }

void	render_frame(void *param)
{
	t_data	*data;
	t_ray	ray;

	data = (t_data *)param;
	draw_ceiling_floor(data);
	raycasting_3d(data, ray);
	draw_minimap(data);
	update_gun_animation(data);
}

void	free_everything(t_data *d)
{
	int	i;

	if (!d)
		return ;
	i = 0;
	while (i < 4)
	{
		if (d->texture[i].img_ptr)
			mlx_delete_image(d->mlx, d->texture[i].img_ptr);
		i++;
	}
	i = 0;
	while (i < 5)
	{
		if (d->gun.frames[i])
			mlx_delete_image(d->mlx, d->gun.frames[i]);
		i++;
	}
	if (d->img)
	{
		mlx_delete_image(d->mlx, d->img);
		d->img = NULL;
	}
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 2 || start_pars(av[1], &data) < 0)
		return (1);
	data.mlx = mlx_init(WIDTH, HEIGHT, "CUB3D", true);
	if (!data.mlx)
		return (1);
	data.img = mlx_new_image(data.mlx, WIDTH, HEIGHT);
	mlx_image_to_window(data.mlx, data.img, 0, 0);
	init_player(&data);
	load_textures(&data);
	load_txt_gun(&data);
	mlx_cursor_hook(data.mlx, &mouse_hook, &data);
	mlx_set_cursor_mode(data.mlx, MLX_MOUSE_DISABLED);
	mlx_loop_hook(data.mlx, handle_input, &data);
	mlx_loop_hook(data.mlx, handle_shooting, &data);
	mlx_loop_hook(data.mlx, render_frame, &data);
	mlx_loop(data.mlx);
	free_everything(&data);
	free_data(&data);
	return (0);
}
