/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MapTols2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slamhaou <slamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 12:02:46 by slamhaou          #+#    #+#             */
/*   Updated: 2026/01/18 09:28:48 by slamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

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
			&& !(str[i] <= 32))
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

char	**fill_arr(char **arr, char **map, int max)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		arr[i] = malloc(max + 1);
		if (!arr[i])
			return (arr[i] = NULL, ft_fre(arr), NULL);
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

char	**get_tst_map(char **map, t_data *data)
{
	int		i;
	int		max;
	char	**arr;

	max = max_lin_map(map, &i);
	arr = malloc(sizeof(char *) * (i + 1));
	if (!arr)
		return (NULL);
	data->map_info.map_h = i;
	data->map_info.map_w = max;
	arr[i] = NULL;
	return (fill_arr(arr, map, max));
}
