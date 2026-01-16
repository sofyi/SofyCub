/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_l.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slamhaou <slamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 13:15:14 by slamhaou          #+#    #+#             */
/*   Updated: 2026/01/12 17:52:29 by slamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

char	*get_new_line(char *romind, int *n)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (romind[i] != '\n')
		i++;
	if (romind[i] == '\n')
		i++;
	new = malloc(1 * (i + 1));
	if (!new)
		return (NULL);
	while (j < i)
	{
		new[j] = romind[j];
		j++;
	}
	new[j] = '\0';
	*n = i;
	return (new);
}

char	*new_rom(char *romind, int i)
{
	char	*new_rom;
	int		j;

	j = 0;
	if (romind[i] == '\0')
		return (free(romind), NULL);
	new_rom = malloc(1 * (ft_strlen(&romind[i]) + 1));
	if (!new_rom)
		return (NULL);
	while (romind[i])
		new_rom[j++] = romind[i++];
	new_rom[j] = '\0';
	free(romind);
	return (new_rom);
}

int	fd_checker(int fd, char **romind)
{
	if (fd < 0)
	{
		free(*romind);
		*romind = NULL;
		return (1);
	}
	return (0);
}

char	*get_line(int fd, char *buffer)
{
	static char	*romind;
	long		red;
	char		*line;
	int			i;

	i = 0;
	if (fd_checker(fd, &romind))
		return (NULL);
	while (serch(romind, '\n') == 0)
	{
		red = read(fd, buffer, BUFFER_SIZE);
		if ((red == 0 && !romind) || red < 0)
			return (NULL);
		if (red == 0 && romind)
		{
			line = str_dup(romind);
			free(romind);
			return (romind = NULL, line);
		}
		buffer[red] = '\0';
		romind = ft_strjoin(romind, buffer);
	}
	line = get_new_line(romind, &i);
	romind = new_rom(romind, i);
	return (line);
}

char	*get_next_line(int fd)
{
	char	*buff;
	char	*line;

	if (fd < 0)
		return (get_line(-1, NULL));
	if (BUFFER_SIZE <= 0)
		return (NULL);
	buff = malloc(BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	line = get_line(fd, buff);
	free(buff);
	return (line);
}
