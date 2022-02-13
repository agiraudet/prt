/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prt.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 16:18:56 by agiraude          #+#    #+#             */
/*   Updated: 2022/02/13 11:52:40 by agiraude         ###   ########.fr       */
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
# include <ctype.h>

# define PRT_BUF_SIZE 500
# define CALL_BUF_SIZE 100
# define C_KEYWORD "auto double int struct break else long switch case enum register typedef char extern return union const float short unsigned continue for signed void default goto sizeof volatile do if static while"

typedef struct	s_lst
{
	struct s_lst	*next;
	void			*data;
}				t_lst;

typedef struct	s_file_prt
{
	char	*name;
	t_lst	*prtlst;
	t_lst	*callst;
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
	int		used;
}				t_settings;

extern t_settings	*g_set;

//srcs/call.c
void  call_add(t_lst **callst, const char *buf);
void  call_cleanall(t_lst *filelst);
t_lst *call_setused(t_lst *filelst);

//srcs/file.c
int   file_check(char *pathname);
t_file_prt	*file_read(const char *pathname);
void	file_del(void *file_ptr);

//srcs/lst.c
t_lst *lst_new(void *data);
void  lst_add(t_lst **list, t_lst *new);
void  lst_clear(t_lst **list, void (*del)(void *));
int   lst_have(t_lst *list, void *this);

//srcs/main.c
void  ft_error(const char *msg1, const char *msg2);

//srcs/print.c
void  print_all(t_lst *filelst);

//srcs/prt.c
t_prt *prt_new(char *line);
void  prt_del(void *prt_ptr);
void  prt_print(t_prt *prt);

//srcs/skip.c
char  skip_comment(FILE *f);
char  skip_macro(FILE *f);
char  skip_bracket(FILE *f, t_lst **callst);

#endif
