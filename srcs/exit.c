/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 11:05:20 by mbarutel          #+#    #+#             */
/*   Updated: 2022/09/17 19:33:42 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	env_delete(t_env *env)
{
	t_env	*ptr;

	ptr = env;
	while (env) // This causes seg fault and I don't know why
	{
		free(env->key);
		free(env->val);
		env = env->next;
	}	
	free(ptr);
}

int	ft_exit(t_env *env, int status)
{
	env_delete(env);
	return(status);
}