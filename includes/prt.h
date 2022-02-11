/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prt.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 16:18:56 by agiraude          #+#    #+#             */
/*   Updated: 2022/02/11 18:15:53 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRT_H
# define PRT_H

# include <stdio.h>
# include <errno.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>

typedef struct	s_lst
{
	struct s_lst	*next;
	void			*data;
}				t_lst;

typedef struct	s_file_prt
{
	char	*name;
	t_lst	*prtlst;
}				t_file_prt;

typedef struct	s_prt
{
	char	*base;
	char	*type;
	char	*expr;
}				t_prt;

typedef struct	s_settings
{
	int		nbspace;
	int		tablen;
	char	indent;
	int		filename;
	int		skipline;
	int		all;
}				t_settings;


void	skip_comment(FILE *f);
void	skip_macro(FILE *f);
void	skip_bracket(FILE *f);


t_prt	*prt_new(char *line);
void	prt_print(t_prt *prt, t_settings *set);
void	prt_del(void *prt_ptr);

t_lst	*lst_new(void *data);
t_lst	*lst_last(t_lst *list);
void	lst_add(t_lst **list, t_lst *new);
void	lst_clear(t_lst **list, void (*del)(void *));

void	print_all(t_lst *filelst, t_settings *set);


t_file_prt	*file_read(const char *pathname);
void		file_del(void *file_ptr);
int	file_check(char *pathname);

void	ft_error(const char *msg1, const char *msg2);
#endif
