/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slamhaou <slamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 16:05:53 by slamhaou          #+#    #+#             */
/*   Updated: 2026/01/14 15:20:13 by slamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	search_replace(char c, char **arr)
{
	int	i;

	i = 0;
	while (arr[0][i])
	{
		if (arr[0][i] == c)
		{
			arr[0][i] = ' ';
			break ;
		}
		i++;
	}
}

int	serch(char *str, char c)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strdup(char *s)
{
	int		i;
	char	*str;

	i = 0;
	str = malloc(ft_strlen(s) + 1);
	while (s[i])
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*skip_spc(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (!str[i])
		return (NULL);
	return (ft_strdup(&str[i]));
}

int	empt_lin(char *lin)
{
	char	*s;

	s = skip_spc(lin);
	if (!s || s[0] == '\n')
		return (free(s), -1);
	free(s);
	return (0);
}
