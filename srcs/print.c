/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 16:15:13 by agiraude          #+#    #+#             */
/*   Updated: 2022/02/13 11:45:05 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prt.h"

void	print_count_spaces(t_lst *filelst)
{
	t_lst	*prtlst;
	int		len;

	g_set->nbspace = 0;
	while (filelst)
	{
		prtlst = ((t_file_prt *)filelst->data)->prtlst;
		while (prtlst)
		{
			len = strlen(((t_prt *)prtlst->data)->type);
			if (len > g_set->nbspace)
				g_set->nbspace = len;
			prtlst = prtlst->next;
		}
		filelst = filelst->next;
	}
	g_set->nbspace++;
}

void	print_file(t_file_prt *file, t_lst *used)
{
	t_lst	*prtlst;

	if (!file || !file->prtlst)
		return ;
	if (g_set->filename)
		printf("//%s\n", file->name);
	prtlst = file->prtlst;
	while (prtlst)
	{
		if ((g_set->used && lst_have(used, prtlst->data)) || !g_set->used)
		prt_print(prtlst->data);
		prtlst = prtlst->next;
	}
}

void	print_all(t_lst *filelst)
{
	t_lst *used;

	used = 0;
	print_count_spaces(filelst);
	if (g_set->used)
	{
		call_cleanall(filelst);
		used = call_setused(filelst);
	}
	while (filelst)
	{
		print_file(filelst->data, used);
		if (g_set->skipline && filelst->next)
			printf("\n");
		filelst = filelst->next;
	}
}
