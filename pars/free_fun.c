/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_fun.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imel-haj <imel-haj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 13:14:59 by slamhaou          #+#    #+#             */
/*   Updated: 2026/01/17 13:06:39 by imel-haj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	ft_free_int(int **tab, int size)
{
	int	i;

	i = 0;
	while (i < size)
		free(tab[i++]);
	free(tab);
}

void	err_msg(char *str, t_data *data)
{
	write(2, str, ft_strlen(str));
	if (!data)
		return ;
	if (data)
		free_data(data);
}

void	ft_fre(char **str)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i])
			free(str[i++]);
		free(str);
	}
}

void	free_data(t_data *data)
{
	int	i;

	i = 0;
	while (data->clr[i])
		free(data->clr[i++]);
	ft_lstclear(&data->path);
	if (data->map_info.map)
		ft_fre(data->map_info.map);
	free(data->clr);
}
