/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slamhaou <slamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 11:32:19 by slamhaou          #+#    #+#             */
/*   Updated: 2026/01/17 22:29:16 by slamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int	s_w_e_n(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

int	count_coma(char *str)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (str[i])
	{
		if (str[i] == ',')
			counter++;
		i++;
	}
	return (counter);
}

int	check_color(char *str, t_data *data, char c, int i)
{
	int		j;
	int		k;
	char	**arr;

	j = 0;
	k = 0;
	if (count_coma(str) != 2)
		return (-1);
	arr = ft_split(str, ',');
	if (!arr || !arr[2])
		return (ft_fre(arr), -1);
	data->clr[i][k++] = c;
	search_replace(c, arr);
	while (arr[j])
	{
		if (check_lin(arr[j]))
			return (ft_fre(arr), -1);
		data->clr[i][k] = ft_atoi(arr[j]);
		if (data->clr[i][k] > 255 || data->clr[i][k] < 0)
			return (ft_fre(arr), -1);
		j++;
		k++;
	}
	return (ft_fre(arr), 0);
}

int	path_s_w_e_n(char *str)
{
	if (str_cmp(str, "NO") || str_cmp(str, "SO")
		|| str_cmp(str, "WE") || str_cmp(str, "EA"))
		return (1);
	return (0);
}

int	check_path_put(char *str, t_data *data)
{
	int		i;
	int		fd;
	char	**arr;

	i = 0;
	arr = ft_split(str, 32);
	if (!arr)
		return (-1);
	while (arr[i])
		i++;
	if (i != 2)
		return (ft_fre(arr), -1);
	i = ft_strlen(arr[1]);
	fd = open(arr[1], O_RDONLY);
	if (arr[1][i - 1] == '/' || fd < 1)
		return (ft_fre(arr), -1);
	if (path_s_w_e_n(arr[0]))
	{
		data->list->texter = str_dup(arr[1]);
		data->list->fd = fd;
		data->list->c = arr[0][0];
		data->list = data->list->next;
	}
	return (ft_fre(arr), 0);
}
