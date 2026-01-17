/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slamhaou <slamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 08:23:40 by slamhaou          #+#    #+#             */
/*   Updated: 2026/01/17 22:32:00 by slamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int	get_map(t_data *data, int fd)
{
	char	*lin;
	char	*long_str;
	char	player;
	int		count_p;

	count_p = 0;
	player = '0';
	long_str = NULL;
	lin = take_lin_data(fd);
	while (true)
	{
		if (!lin)
			break ;
		if (how_many_pl(&player, lin, &count_p) < 0 || empt_lin(lin))
			return (free(long_str), free(lin), get_next_line(-1), -1);
		long_str = ft_strjoin(long_str, lin);
		free(lin);
		lin = get_next_line(fd);
	}
	if (!long_str || player == '0')
		return (free(long_str), -1);
	data->map_info.map = ft_split(long_str, '\n');
	if (!data->map_info.map)
		return (free(long_str), -1);
	return (free(long_str), 0);
}

int	get_path_color(int fd, t_data *data)
{
	int		i;
	char	*str;
	char	*lin;

	i = 0;
	while (i < TOTALCOLRSTXTUR)
	{
		str = get_next_line(fd);
		if (!str)
			break ;
		lin = skip_spc(str);
		if (!lin)
			return (free(str), get_next_line(-1), -1);
		free(str);
		if (lin[0] != '\n' && lin[0])
		{
			if (check_lin_p_c(lin, data) == -1)
				return (free(lin), get_next_line(-1), -1);
			i++;
		}
		free(lin);
	}
	if (i == 0)
		return (write(1, "erorr no path no colors\n", 24), -1);
	return (0);
}

int	init_data(t_data *data)
{
	int	i;

	i = 0;
	data->clr = malloc(sizeof(int *) * 3);
	if (!data->clr)
		return (write(1, "fild init data", 14), -1);
	while (i < 2)
	{
		data->clr[i] = malloc(sizeof(int) * 4);
		if (!data->clr[i])
			return (ft_free_int(data->clr, i), -1);
		i++;
	}
	data->clr[i] = NULL;
	i = 0;
	data->path = ft_lstnew();
	if (!data->path)
		return (ft_free_int(data->clr, 2), -1);
	while (i < 3)
	{
		ft_lstadd_back(&data->path, ft_lstnew());
		i++;
	}
	data->list = data->path;
	return (data->map_info.map = NULL, 0);
}

int	dot_cub(char *str)
{
	int	i;

	i = ft_strlen(str);
	i--;
	while (i > 0 && str[i] != '.')
		i--;
	if (i == 0 || str[i - 1] == '/')
		return (0);
	if (str[i] == '.' && str_cmp(&str[i + 1], "cub"))
		return (1);
	return (0);
}

int	start_pars(char *str, t_data *data)
{
	int		fd;
	char	**tst_map;

	if (!dot_cub(str))
		return (write(2, "ERORR FILE Name\n", 17), -1);
	fd = open(str, O_RDONLY);
	if (fd < 0)
		return (write(2, "Erorr file \n", 13), -1);
	if (init_data(data))
		return (close(fd), -1);
	if (get_path_color(fd, data) == -1)
		return (close (fd), free_data(data), -1);
	if (get_map(data, fd) < 0)
		return (err_msg("Erorr: map erorr\n", data), close(fd), -1);
	tst_map = get_tst_map(data->map_info.map, data);
	if (!tst_map || check_map(tst_map) < 0)
	{
		err_msg("Erorr: map erorr\n", data);
		return (close(fd), ft_fre(tst_map), -1);
	}
	ft_fre(tst_map);
	get_next_line(-1);
	return (close(fd), 0);
}
