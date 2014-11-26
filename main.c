/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plavaux <plavaux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/22 14:47:35 by plavaux           #+#    #+#             */
/*   Updated: 2014/11/26 15:26:50 by plavaux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** <stdio.h> is required for perror.
** FYI: http://www.gnu.org/software/libc/manual/html_node/Testing-File-Type.html
*/

#include <dirent.h>
#include <stdio.h>
#include <errno.h>
#include <sys/stat.h>
#include "libft/libft.h"

static void			print_item(char *item, char *args, int folder)
{
	if (folder)
	{
		ft_putstr("\033[34m\033[1m");
		ft_putstr(item);
		if (args)
			if (ft_strchr(args, 'p'))
				ft_putchar('/');
		ft_putendl("\033[0m");
	}
}

int					list_dir(char *args, char *path)
{
	DIR				*dir;
	struct dirent	*dp;
	int				status;
	struct stat		st_buf;

	(void)status;
	if (!(dir = opendir(path)))
	{
		perror("opendir failed");
		return (0);
	}
	while ((dp = readdir(dir)))
	{
		status = stat(dp->d_name, &st_buf);
		if (!ft_strcmp(dp->d_name, ".") || !ft_strcmp(dp->d_name, ".."))
			continue;
		(S_ISDIR (st_buf.st_mode)) ? print_item(dp->d_name, args, 1)
			: ft_putendl(dp->d_name);
	}
	if (closedir(dir) == -1)
		perror("closedir failed");
	return (0);
}

int					args_check(char *args)
{
	return (!ft_strchr(args, '-') || !ft_strchr(args, 'p'));
}

int					main(int argc, char **argv)
{
	if (argc < 2)
	{
		ft_putendl("Usage: ft_list_dir [-p] <directory name>");
		return (-1);
	}
	if (argc > 3)
	{
		ft_putendl("Too many arguments.");
		return (-1);
	}
	if (argc < 3)
		list_dir(NULL, argv[1]);
	if (argc == 3)
	{
		if (args_check(argv[1]))
		{
			ft_putendl("Invalid argument(s).");
			return (-1);
		}
		else
			list_dir(argv[1], argv[2]);
	}
	return (0);
}
