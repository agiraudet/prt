/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 15:21:51 by agiraude          #+#    #+#             */
/*   Updated: 2022/02/11 18:15:11 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prt.h"

int	file_check(char *pathname)
{
	char	*end;

	end = strrchr(pathname, '.');
	if (!end || strcmp(end, ".c") != 0)
	{
		ft_error(pathname, "not a valid '.c' file");
		return (0);
	}
	if (access(pathname, R_OK) != 0)
	{
		ft_error(pathname, strerror(errno));
		return (0);
	}
	return (1);
}

void	file_addprt(t_lst **prtlst, char *buf)
{
	if (!buf[0])
		return ;
	lst_add(prtlst, lst_new(prt_new(buf)));
}

t_lst	*file_parse(FILE *f)
{
	char	c;
	int		i;
	char	buf[500];
	t_lst	*prtlst;

	i = 0;
	c = fgetc(f);
	prtlst = 0;
	while (c != EOF)
	{
		if (c == '/')
			skip_comment(f);
		else if (c == '#')
			skip_macro(f);
		else if (c == '{')
		{
			buf[i] = 0;
			file_addprt(&prtlst, &buf[0]);
			memset((void *)buf, 0, 500);
			i = 0;
			skip_bracket(f);
		}
		else if (c != '\n')
			buf[i++] = c;
		c = fgetc(f);
	}
	return (prtlst);
}

void	file_del(void *file_ptr)
{
	t_file_prt	*file;

	file = (t_file_prt *)file_ptr;
	free(file->name);
	lst_clear(&file->prtlst, &prt_del);
	free(file);
}

t_file_prt	*file_read(const char *pathname)
{
	FILE		*f;
	t_file_prt	*fileprt;

	fileprt = (t_file_prt *)malloc(sizeof(t_file_prt));
	if (!fileprt)
	{
		ft_error("malloc", 0);
		return (0);
	}
	f = fopen(pathname, "r");
	if (!f)
	{
		ft_error(pathname, "failed to open file");
		return (0);
	}
	fileprt->prtlst = file_parse(f);
	fclose(f);
	fileprt->name = strdup(pathname);
	return (fileprt);
}
