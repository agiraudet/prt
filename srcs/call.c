/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 21:57:21 by agiraude          #+#    #+#             */
/*   Updated: 2022/02/13 11:43:44 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prt.h"

char	*call_format(const char *buf)
{
	int		end;
	int		start;
	char	*call;

	end = strlen(buf) - 1;
	while (end && strchr(" \n\t", buf[end]) != 0)
		end--;
	start = end;
//	while (start && strchr("*&{};()= \t\n", buf[start]) == 0)
	while (start && (isalnum(buf[start]) || buf[start] == '_' || buf[start] == '_'))
		start--;
//	while (start < end && strchr("*&{};()= \t\n", buf[start]) != 0)
	while (start < end && !(isalpha(buf[start]) || buf[start] == '-' || buf[start] == '_'))
		start++;
	if (start >= end)
		return (0);
	call = strndup(&buf[start], end - start + 1);
	if (strstr(C_KEYWORD, call) == 0)
		return (call);
	free(call);
	return (0);
}

int	call_inlst(t_lst *list, const char *call)
{
	while (list)
	{
		if (strcmp(list->data, call) == 0)
			return (1);
		list = list->next;
	}
	return (0);
}

t_prt	*call_inexpr(t_lst *list, const char *call)
{
	while (list)
	{
		if (strstr(((t_prt *)list->data)->expr, call) != 0)
			return ((t_prt*)list->data);
		list = list->next;
	}
	return (0);
}

void	call_add(t_lst **callst, const char *buf)
{
	char	*call;

	call = call_format(buf);
	if (call && call_inlst(*callst, call) == 0)
		lst_add(callst, lst_new(call));
}

void	call_cleanlst(t_file_prt *prt)
{
	t_lst	*cursor;
	t_lst	*prev;

	cursor = prt->callst;
	if (!cursor)
		return ;
	prev = 0;
	while (!call_inexpr(prt->prtlst, cursor->data))
	{
		if (!cursor->next)
			break ;
		prev = cursor;
		cursor = cursor->next;
	}
	if (prev)
		prev->next = cursor->next;
	else
		prt->callst = cursor->next;
	if (cursor)
	{
		free(cursor->data);
		free(cursor);
	}
}

void	call_cleanall(t_lst *filelst)
{
	while (filelst)
	{
		call_cleanlst(filelst->data);
		filelst = filelst->next;
	}
}

void	call_used(t_lst **used, t_file_prt *file, t_lst *filelst)
{
	t_lst	*callst;
	t_lst	*file_cursor;
	t_prt	*prt;

	callst = file->callst;
	while (callst)
	{
		file_cursor = filelst;
		while (file_cursor)
		{
			if (file != file_cursor->data)
			{
				prt = call_inexpr(((t_file_prt *)file_cursor->data)->prtlst, callst->data);
				if (prt && lst_have(*used, prt) == 0)
					lst_add(used, lst_new(prt));
			}
			file_cursor= file_cursor->next;
		}
		callst = callst->next;
	}
}

t_lst	*call_setused(t_lst *filelst)
{
	t_lst	*used;
	t_lst	*file;

	used = 0;
	file = filelst;
	while (file)
	{
		call_used(&used, file->data, filelst);
		file = file->next;
	}
	return (used);
}
