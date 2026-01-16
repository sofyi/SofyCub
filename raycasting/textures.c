/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slamhaou <slamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 23:16:01 by imel-haj          #+#    #+#             */
/*   Updated: 2026/01/16 16:41:56 by slamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	put_text_gun(char **paths)
{
	paths[0] = "./frames/shotgun1.png";
	paths[1] = "./frames/shotgun2.png";
	paths[2] = "./frames/shotgun3.png";
	paths[3] = "./frames/shotgun4.png";
	paths[4] = "./frames/shotgun5.png";
}

void	load_txt_gun(t_data *data)
{
	int				i;
	mlx_texture_t	*texture;
	char			*paths[5];
	int				x;
	int				y;

	i = 0;
	put_text_gun(paths);
	while (i < 5)
	{
		texture = mlx_load_png(paths[i]);
		if (!texture)
			exit(1);
		data->gun.frames[i] = mlx_texture_to_image(data->mlx, texture);
		mlx_delete_texture(texture);
		x = (WIDTH / 2) - (data->gun.frames[i]->width / 2);
		y = HEIGHT - data->gun.frames[i]->height;
		mlx_image_to_window(data->mlx, data->gun.frames[i], x, y);
		data->gun.frames[i]->enabled = false;
		i++;
	}
	data->gun.frames[0]->enabled = true;
	data->gun.current_frame = 0;
	data->gun.is_shooting = false;
}

void	load_textures(t_data *data)
{
	int				i;
	t_path			*list;
	mlx_texture_t	*tex;

	i = 0;
	list = data->path;
	while (list)
	{
		tex = mlx_load_png(list->texter);
		if (!tex)
		{
			exit(0);
		}
		data->texture[i].img_ptr = mlx_texture_to_image(data->mlx, tex);
		data->texture[i].width = tex->width;
		data->texture[i].height = tex->height;
		mlx_delete_texture(tex);
		i++;
		list = list->next;
	}
}
