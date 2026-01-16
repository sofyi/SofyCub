/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Libft2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slamhaou <slamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 15:15:03 by slamhaou          #+#    #+#             */
/*   Updated: 2026/01/14 22:26:22 by slamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int	is_num(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

void	ft_lstadd_back(t_path **lst, t_path *new)
{
	t_path	*list;

	if (!lst || !new)
		return ;
	list = *lst;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	while (list->next)
		list = list->next;
	list->next = new;
}

t_path	*ft_lstnew(void)
{
	t_path	*nod;

	nod = malloc(sizeof(t_path));
	if (!nod)
		return (NULL);
	nod->fd = -1;
	nod->c = '0';
	nod->texter = NULL;
	nod->next = NULL;
	return (nod);
}

void	ft_lstdelone(t_path *lst)
{
	if (!lst)
		return ;
	free(lst->texter);
	lst->texter = NULL;
	free(lst);
	lst = NULL;
}

void	ft_lstclear(t_path **lst)
{
	t_path	*list;

	if (!lst)
		return ;
	while (*lst)
	{
		list = *lst;
		*lst = (*lst)->next;
		close(list->fd);
		ft_lstdelone(list);
	}
	*lst = NULL;
}
