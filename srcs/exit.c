/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 11:05:20 by mbarutel          #+#    #+#             */
/*   Updated: 2022/09/21 18:00:01 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	arg_clean(char **arg, char *line)
{
	char **ptr;

	ptr = arg;
	if (line)
		free(line);
	while (*arg)
	{
		free(*arg);
		arg++;
	}
	free(ptr);
	ptr = NULL;
}

void	env_clean(char **env)
{
	char **ptr;

	ptr = env;
	while (*ptr)
	{
		free(*ptr);
		ptr++;
	}
	free(env);
	env = NULL;
}

int	ft_exit(t_session *session, char *message)
{
	if (message)
		ft_printf("%s\n", message);
	env_clean(session->env);
	return (SUCCESS);
}