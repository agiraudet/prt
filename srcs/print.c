/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 16:15:13 by agiraude          #+#    #+#             */
/*   Updated: 2022/02/11 17:57:23 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prt.h"

void	print_count_spaces(t_lst *filelst, t_settings *set)
{
	t_lst	*prtlst;
	int		len;

	set->nbspace = 0;
	while (filelst)
	{
		prtlst = ((t_file_prt *)filelst->data)->prtlst;
		while (prtlst)
		{
			len = strlen(((t_prt *)prtlst->data)->type);
			if (len > set->nbspace)
				set->nbspace = len;
			prtlst = prtlst->next;
		}
		filelst = filelst->next;
	}
	set->nbspace++;
}

void	print_file(t_file_prt *file, t_settings *set)
{
	t_lst	*prtlst;

	if (!file || !file->prtlst)
		return ;
	if (set->filename)
		printf("//%s\n", file->name);
	prtlst = file->prtlst;
	while (prtlst)
	{
		prt_print(prtlst->data, set);
		prtlst = prtlst->next;
	}
}

void	print_all(t_lst *filelst, t_settings *set)
{
	print_count_spaces(filelst, set);
	while (filelst)
	{
		print_file(filelst->data, set);
		if (set->skipline && filelst->next)
			printf("\n");
		filelst = filelst->next;
	}
}
