/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 16:14:08 by agiraude          #+#    #+#             */
/*   Updated: 2022/02/11 19:09:32 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prt.h"

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
	printf("  -h\tdisplay this help and exit\n");
	printf("\nExamples:\n  %s foo.c", progname);
	printf("\tOuputs prototypes form foo.c.\n");
	printf("\n- WIP -\n");
	exit(EXIT_SUCCESS);
}

void	set_settings(int argc, char **argv, t_settings *set)
{
	int	opt;

	set->indent = '\t';
	set->tablen = 4;
	set->indent = ' ';
	set->skipline = 0;
	set->filename = 0;
	set->all = 0;
	while ((opt = getopt(argc, argv, "snfah")) != -1)
	{
		if (opt == 's')
			set->indent = ' ';
		else if (opt == 'n')
			set->skipline = 1;
		else if (opt == 'f')
			set->filename = 1;
		else if (opt == 'a')
			set->all = 1;
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
	t_settings	set;
	t_lst		*filelst;

	ft_error(argv[0], 0);
	set_settings(argc, argv, &set);
	if (optind >= argc)
		exit(EXIT_SUCCESS);
	filelst = 0;
	while (argv[optind])
	{
		if (file_check(argv[optind]))
			lst_add(&filelst, lst_new(file_read(argv[optind])));
		optind++;
	}
	print_all(filelst, &set);
	lst_clear(&filelst, &file_del);
	exit(EXIT_SUCCESS);
}
