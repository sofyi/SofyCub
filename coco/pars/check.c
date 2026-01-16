/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slamhaou <slamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 15:32:46 by slamhaou          #+#    #+#             */
/*   Updated: 2026/01/14 15:16:25 by slamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int	check_lin_p_c(char *lin, t_data *data)
{
	int	chk;

	chk = color_or_paht(lin);
	if (chk == -1 || check_put(chk, lin, data) == -1)
	{
		if (chk == -1)
			write(1, "invalid caracter\n", 18);
		get_next_line(-1);
		return (-1);
	}
	return (0);
}

int	color_or_paht(char *str)
{
	char	c;

	if (!str[0] || str[0] == '\n')
		return (0);
	if (str[0] == 'F' || str[0] == 'C')
		return (str[0]);
	c = str[2];
	str[2] = '\0';
	if (str_cmp("NO", str) || str_cmp("SO", str)
		|| str_cmp("WE", str) || str_cmp("EA", str))
		return (str[2] = c, str[0]);
	str[2] = c;
	return (-1);
}

int	check_lin(char *str)
{
	int		i;
	char	*lin;

	i = 0;
	lin = skip_spc(str);
	if (!lin)
		return (-1);
	while (lin[i] && lin[i] >= '0' && lin[i] <= '9')
		i++;
	while (lin[i] && lin[i] <= 32)
		i++;
	if (lin[i] != '\0' && lin[i] != '\n')
		return (free(lin), -1);
	free(lin);
	return (0);
}

int	path_texter(t_data *data, char *lin, char c)
{
	t_path	*search;

	search = data->path;
	while (search)
	{
		if (search->c == c)
		{
			write(1, "Error:Texture path[NO/SO/WE/EA] is duplicated\n", 47);
			return (-1);
		}
		search = search->next;
	}
	if (check_path_put(lin, data) < 0)
		return (write(2, "Error: Invalid Path\n", 20), -1);
	return (0);
}

int	check_put(char c, char *str, t_data *data)
{
	static int	i;
	int			j;

	j = 0;
	while (str[j] && str[j] != '\n')
		j++;
	if (str[j] == '\n')
		str[j] = '\0';
	if (s_w_e_n(c))
	{
		if (path_texter(data, str, c) < 0)
			return (-1);
	}
	else if (c == 'C' || c == 'F')
	{
		if (check_color(str, data, c, i) < 0)
			return (write(2, "Eror: Invalid color..\n", 22), -1);
		i++;
	}
	return (0);
}
