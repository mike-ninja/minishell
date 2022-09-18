/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 20:42:38 by mbarutel          #+#    #+#             */
/*   Updated: 2022/09/17 19:31:44 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_print(t_env *env)
{
	while (env)
	{
		ft_printf("%s=%s\n", env->key, env->val);
		env = env->next;
	}
	return (1);
}

static void	remove_node(t_env *prev, t_env *curr)
{
	t_env *ptr;

	ptr = curr->next;
	free(curr->key);
	free(curr->val);
	free(curr);
	prev->next = ptr;
}

int	unset_env(t_env *env, char **input)
{
	t_env	*prev;

	prev = NULL;
	while (env)
	{
		if (ft_strcmp(env->key, input[1]) == 0)
		{
			remove_node(prev, env);
			return (1);
		}
		prev = env;
		env = env->next;
	}
	return (0);
}

int set_env(t_env *env, char **input)
{
	t_env	*node;
	
	node = env_node();
	if (!node)
		return (0);
	node->key = ft_strdup(ft_strsep(&input[1], "="));
	node->val = ft_strdup(input[1]);
	while (env->next)
		env = env->next;
	env->next = node;
	return (1);
}
