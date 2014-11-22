/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plavaux <plavaux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/22 14:47:35 by plavaux           #+#    #+#             */
/*   Updated: 2014/11/22 21:42:24 by plavaux          ###   ########.fr       */
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

static void			print_item(char *item, int folder)
{
	if (folder)
	{
		ft_putstr("\033[34m\033[1m");
		ft_putstr(item);
		ft_putendl("\033[0m");
	}
}

int					list_dir(char *path)
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
		if ((int)ft_strlen(dp->d_name) == 1 && dp->d_name[0] == '.')
			continue;
		if (dp->d_name[1] != '.')
			(S_ISDIR (st_buf.st_mode)) ? print_item(dp->d_name, 1)
				: ft_putendl(dp->d_name);
	}
	if (closedir(dir) == -1)
		perror("closedir failed");
	return (0);
}

int					main(int argc, char **argv)
{
	if (argc < 2)
	{
		ft_putendl("Usage: ft_list_dir <directory name>");
		return (-1);
	}
	list_dir(argv[1]);
	return (0);
}
