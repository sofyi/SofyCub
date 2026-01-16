/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MapTols2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slamhaou <slamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 12:02:46 by slamhaou          #+#    #+#             */
/*   Updated: 2026/01/14 16:52:47 by slamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int	lin_is_sps(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] <= 32) && str[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

int	wall_check(char *str, char c)
{
	int	i;

	i = 0;
	if (c == 'c')
	{
		if (*str != ' ' && *str != '1')
			return (1);
		return (0);
	}
	if (c == 's')
	{
		while (str[i])
		{
			if (str[i] != ' ' && str[i] != '1')
				return (1);
			i++;
		}
		return (0);
	}
	return (0);
}

int	how_many_pl(char *p, char *str, int *count)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '\n')
	{
		if (s_w_e_n(str[i]))
		{
			*p = str[i];
			(*count)++;
		}
		if (str[i] != '0' && str[i] != '1' && s_w_e_n(str[i]) == 0
			&& !(str[i] <= 32) && str[i] != 'D')
			return (-1);
		i++;
	}
	if (*count > 1)
		return (-1);
	return (0);
}

int	max_lin_map(char **map, int *len_map)
{
	int	i;
	int	j;
	int	max;

	i = 0;
	j = 0;
	max = 0;
	while (map[i])
	{
		j = ft_strlen(map[i]);
		if (j > max)
			max = j;
		i++;
	}
	*len_map = i;
	return (max);
}

char	**get_tst_map(char **map, t_data *data)
{
	int		i;
	int		j;
	int		max;
	char	**arr;

	i = 0;
	max = max_lin_map(map, &i);
	arr = malloc(sizeof(char *) * (i + 1));
	data->map_info.map_h = i;
	data->map_info.map_w = max;
	arr[i] = NULL;
	i = 0;
	while (map[i])
	{
		j = 0;
		arr[i] = malloc(max + 1);
		while (map[i][j])
		{
			arr[i][j] = map[i][j];
			j++;
		}
		while (j < max)
			arr[i][j++] = ' ';
		arr[i++][j] = '\0';
	}
	return (arr);
}
