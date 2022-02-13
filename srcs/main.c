/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 16:14:08 by agiraude          #+#    #+#             */
/*   Updated: 2022/02/13 11:50:58 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prt.h"

t_settings *g_set;

void	ft_error(const char *msg1, const char *msg2)
{
	static char	*progname = 0;

	if (!progname)
		progname = (char *)msg1;
	else if (!msg2)
		printf("%s: %s\n", progname, msg1);
	else
		printf("%s: %s: %s\n", progname, msg1, msg2);
}

void	help(char *progname)
{
	printf("Usage: %s [OPTION]... [FILE.c]...\n", progname);
	printf("Print function's prototype from a '.c' file to standard output.\n");
	printf("\nThis tool is a work in progress, dont sudo it.\n\n");
	printf("  -s\tindent with spaces instead of tabs\n");
	printf("  -n\tadd a newline between prototypes of differents files\n");
	printf("  -f\tprint filename before protoypes, adding '//' before it\n");
	printf("  -a\tprint static fonctions prototype as well\n");
	printf("  -u\tprint only functions defined in a file and called from an other one\n");
	printf("  -h\tdisplay this help and exit\n");
	printf("\nExamples:\n  %s foo.c", progname);
	printf("\tOuputs prototypes form foo.c.\n");
	printf("\n- WIP -\n");
	exit(EXIT_SUCCESS);
}

void	set_settings(int argc, char **argv)
{
	int	opt;

	g_set = (t_settings *)malloc(sizeof(t_settings));
	if (!g_set)
		exit(EXIT_FAILURE);
	g_set->indent = '\t';
	g_set->tablen = 4;
	g_set->indent = ' ';
	g_set->skipline = 0;
	g_set->filename = 0;
	g_set->all = 0;
	g_set->used = 0;
	while ((opt = getopt(argc, argv, "snfahu")) != -1)
	{
		if (opt == 's')
			g_set->indent = ' ';
		else if (opt == 'n')
			g_set->skipline = 1;
		else if (opt == 'f')
			g_set->filename = 1;
		else if (opt == 'a')
			g_set->all = 1;
		else if (opt == 'u')
			g_set->used = 1;
		else if (opt == 'h')
			help(argv[0]);
		else
		{
			printf("Try '%s -h' for more information\n", argv[0]);
			exit(EXIT_FAILURE);
		}
	}
}

int	main(int argc, char **argv)
{
	t_lst		*filelst;

	ft_error(argv[0], 0);
	set_settings(argc, argv);
	if (optind >= argc)
		exit(EXIT_SUCCESS);
	filelst = 0;
	while (argv[optind])
	{
		if (file_check(argv[optind]))
			lst_add(&filelst, lst_new(file_read(argv[optind])));
		optind++;
	}
	print_all(filelst);
	lst_clear(&filelst, &file_del);

	exit(EXIT_SUCCESS);
}
