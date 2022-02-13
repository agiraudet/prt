/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 16:40:57 by agiraude          #+#    #+#             */
/*   Updated: 2022/02/12 17:46:26 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prt.h"

t_lst	*lst_new(void *data)
{
	t_lst	*new;

	new = (t_lst *)malloc(sizeof(t_lst));
	if (!new)
		return (0);
	new->data = data;
	new->next = 0;
	return (new);
}

t_lst	*lst_last(t_lst *list)
{
	if (!list)
		return (0);
	while (list->next)
		list = list->next;
	return (list);
}

void	lst_add(t_lst **list, t_lst *new)
{
	t_lst	*last;

	if (!(*list))
		*list = new;
	else
	{
		last = lst_last(*list);
		last->next = new;
	}
}

void	lst_clear(t_lst **list, void (*del)(void *))
{
	t_lst	*cursor;

	if (!list)
		return ;
	while (*list)
	{
		cursor = (*list)->next;
		del((*list)->data);
		free(*list);
		*list = cursor;
	}
}

int	lst_have(t_lst *list, void *this)
{
	while (list)
	{
		if (list->data == this)
			return (1);
		list = list->next;
	}
	return (0);
}
