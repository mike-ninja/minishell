/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 11:05:20 by mbarutel          #+#    #+#             */
/*   Updated: 2022/09/30 12:43:34 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	arg_clean(char **arg, char *line)
{
	int i;

	i = -1;
	if (line)
		free(line);
	while (arg[++i])
		free(arg[i]);
	free(arg);
	arg = NULL;
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

void	ft_exit(t_session *sesh, char *message, int status)
{
	if (message)
		ft_printf("-minishell: %s: %s\n", *sesh->arg, message);
	env_clean(sesh->env);
	arg_clean(sesh->arg, NULL);
	exit(status);
}