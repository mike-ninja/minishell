/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 13:21:43 by mbarutel          #+#    #+#             */
/*   Updated: 2022/09/18 17:20:54 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern	char **environ;

void	env_del(char **env)
{
	char **ptr;

	ptr = env;
	while (*ptr)
		free(*ptr++);
	free(env);
	env = NULL;
}

size_t	env_len(char **env)
{
	size_t len;

	len = 0;
	while (env[len])
		len++;
	return (len);
}

char	**env_init(void)
{
	char	**env;
	char	**ptr;

	ptr = (char **)malloc(sizeof(char *) * env_len(environ) + 1);
	if (!ptr)
		return(NULL);
	env = ptr;
	while (*environ)
	{
		*ptr = ft_strdup(*environ);
		environ++;
		ptr++;
	}
	*ptr = NULL;
	return (env);
}