/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 16:09:33 by agiraude          #+#    #+#             */
/*   Updated: 2022/02/12 13:55:25 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prt.h"

char	skip_comment(FILE *f)
{
	char	c;

	c = fgetc(f);
	if (c == EOF)
		return (c);
	if (c == '/')
		while (c != '\n' && c != EOF)
			c = fgetc(f);
	else if (c == '*')
	{
		while (c != EOF)
		{
			c = fgetc(f);
			if (c == '*')
			{
				c = fgetc(f);
				if (c == '/' || c == EOF)
					return (c);
			}
		}
	}
	return (c);
}

char	skip_macro(FILE *f)
{
	char	c;

	c = fgetc(f);
	while (c != EOF && c != '\n')
		c = fgetc(f);
	return (c);
}

char	skip_bracket(FILE *f, t_lst **callst)
{
	char	c;
	int		i;
	int		bracket;
	char	buf[CALL_BUF_SIZE];

	bracket = 1;
	i = 0;
	c = fgetc(f);
	while (c != EOF && bracket != 0)
	{
		if (c == '{')
			bracket++;
		else if (c == '}')
			bracket--;
		else
		{
			if (c == '(')
			{
				buf[i] = 0;
				if (g_set->used)
					call_add(callst, buf);
				memset(buf, 0, sizeof(char) * CALL_BUF_SIZE);
				i = 0;
			}
			else if (c == ';')
			{
				i = 0;
				memset(buf, 0, sizeof(char) * CALL_BUF_SIZE);
			}
			else
				buf[i++] = c;
		}				
		c = fgetc(f);
	}
	return (c);
}
