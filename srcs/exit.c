/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 11:05:20 by mbarutel          #+#    #+#             */
/*   Updated: 2022/09/19 12:58:14 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static void	env_delete(t_env *env)
// {
// 	t_env	*ptr;

// 	ptr = env;
// 	while (env) // This causes seg fault and I don't know why
// 	{
// 		free(env->key);
// 		free(env->val);
// 		env = env->next;
// 	}	
// 	free(ptr);
// }

// int	ft_exit(t_env *env, int status)
// {
// 	env_delete(env);
// 	return(status);
// }

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
		ft_printf("%s", message);
	env_clean(session->env);
	return (1);
}