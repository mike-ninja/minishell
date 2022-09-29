/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 11:05:20 by mbarutel          #+#    #+#             */
/*   Updated: 2022/09/29 15:30:46 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	arg_clean(char **arg, char *line)
{
	char **ptr;

	ptr = arg;
	if (line)
		free(line);
	// char **art;
	// art = arg;
	// while (*art)
	// {
	// 	ft_printf("{%s}\n", *art);
	// 	art++;
	// }
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

int	ft_exit(t_session *sesh, char *message)
{
	if (message)
		ft_printf("-minishell: %s: %s\n", *sesh->arg, message);
	env_clean(sesh->env);
	arg_clean(sesh->arg, NULL);
	return (SUCCESS);
}