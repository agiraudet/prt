/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prt.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 15:51:17 by agiraude          #+#    #+#             */
/*   Updated: 2022/02/11 17:45:23 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prt.h"

void	prt_split(t_prt *prt, char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '(')
		i++;
	while (i && line[i] != ' ' && line[i] != '\t')
		i--;
	prt->expr = strdup(&line[i + 1]);
	while (i && (line[i] == ' ' || line[i] == '\t'))
		i--;
	prt->type = strndup(line, i + 1);
}

t_prt	*prt_new(char *line)
{
	t_prt	*prt;

	prt = (t_prt *)malloc(sizeof(t_prt));
	if (!prt)
		return (0);
	prt->base = strdup(line);
	prt->expr = 0;
	prt->type = 0;
	prt_split(prt, line);
	return (prt);
}

void	prt_del(void *prt_ptr)
{
	t_prt	*prt;

	prt = (t_prt *)prt_ptr;
	free(prt->base);
	free(prt->expr);
	free(prt->type);
	free(prt);
}

void	prt_print(t_prt *prt, t_settings *set)
{
	int	i;

	if (!set->all && strstr(prt->type, "static") != 0)
		return ;
	printf("%s", prt->type);
	i = strlen(prt->type);
	while (i < set->nbspace)
	{
		printf("%c", set->indent);
		if (set->indent == ' ')
			i++;
		else if (set->indent == '\t')
			i += set->tablen;
	}
	if (set->indent == '\t' && i <= set->nbspace + 1)
		printf("%c", set->indent);
	printf("%s", prt->expr);
	printf(";\n");
}
