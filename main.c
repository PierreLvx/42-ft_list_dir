/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plavaux <plavaux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/22 14:47:35 by plavaux           #+#    #+#             */
/*   Updated: 2014/11/22 16:18:14 by plavaux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** <stdio.h> is required for perror.
*/

#include <dirent.h>
#include <stdio.h>
#include <sys/types.h>
#include <errno.h>
#include "libft/libft.h"

int					list_dir(char *path)
{
	DIR				*dir;
	struct dirent	*dp;

	if (!(dir = opendir(path)))
	{
		perror("opendir failed");
		return (0);
	}
	ft_putendl("\033[32mOpened directory stream.\033[0m");
	while ((dp = readdir(dir)))
	{
		if ((int)ft_strlen(dp->d_name) == 1 && dp->d_name[0] == '.')
			continue;
		if (dp->d_name[1] != '.')
			ft_putendl(dp->d_name);
	}
	if (closedir(dir) == -1)
	{
		perror("closedir failed");
		return (0);
	}
	ft_putendl("\033[32mClosed directory stream.\033[0m");
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
