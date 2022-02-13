/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 15:21:51 by agiraude          #+#    #+#             */
/*   Updated: 2022/02/12 13:36:28 by agiraude         ###   ########.fr       */
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

void	file_addprt(t_lst **prtlst, char *buf, int *i)
{
	buf[*i] = 0;
	if (buf[0])
		lst_add(prtlst, lst_new(prt_new(buf)));
	*i = 0;
	memset(buf, 0, sizeof (char) * PRT_BUF_SIZE);
}

void	file_parse(FILE *f, t_file_prt *fileprt)
{
	char	c;
	int		i;
	char	buf[PRT_BUF_SIZE];

	i = 0;
	c = fgetc(f);
	while (c != EOF)
	{
		if (c == '/')
			c =skip_comment(f);
		else if (c == '#')
			c =skip_macro(f);
		else if (c == '{')
		{
			file_addprt(&fileprt->prtlst, buf, &i);
			c =skip_bracket(f, &fileprt->callst);
		}
		else if (c != '\n')
			buf[i++] = c;
		if (c == ';')
		{
			i = 0;
			memset(buf, 0, sizeof(char) * PRT_BUF_SIZE);
		}
		if (c == EOF)
			break;
		c = fgetc(f);
	}
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
	fileprt->prtlst = 0;
	fileprt->callst = 0;
	f = fopen(pathname, "r");
	if (!f)
	{
		ft_error(pathname, "failed to open file");
		return (0);
	}
	file_parse(f, fileprt);
	fclose(f);
	fileprt->name = strdup(pathname);
	return (fileprt);
}
