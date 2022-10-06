/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_expansion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 17:53:31 by mbarutel          #+#    #+#             */
/*   Updated: 2022/10/06 19:16:01 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <dirent.h>

static char	*find_user(char *user)
{
	DIR				*dir;
	char			*addr;
	struct dirent	*dent;

	dent = NULL;
	addr = "/Users/";
	dir = opendir(addr);
	dent = readdir(dir);
	while (dent)
	{
		if (!ft_strcmp(dent->d_name, user))
		{
			closedir(dir);
			return (ft_strjoin(addr, user));
		}
		dent = readdir(dir);
	}
	closedir(dir);
	return (NULL);
}

void	user_expansion(char **arg, char **env)
{
	char	*user;

	user = find_user(&arg[0][1]);
	if (user)
	{
		ft_strdel(arg);
		*arg = user;
	}
}
