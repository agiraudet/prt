/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 16:09:33 by agiraude          #+#    #+#             */
/*   Updated: 2022/02/11 17:52:50 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prt.h"

void	skip_comment(FILE *f)
{
	char	c;

	c = fgetc(f);
	if (c == EOF)
		return ;
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
					return ;
			}
		}
	}
}

void	skip_macro(FILE *f)
{
	char	c;

	c = fgetc(f);
	while (c != EOF && c != '\n')
		c = fgetc(f);
}

void	skip_bracket(FILE *f)
{
	char	c;
	int		bracket;

	bracket = 1;
	c = fgetc(f);
	while (c != EOF && bracket != 0)
	{
		if (c == '{')
			bracket++;
		if (c == '}')
			bracket--;
		c = fgetc(f);
	}
}
