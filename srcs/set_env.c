/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 13:21:43 by mbarutel          #+#    #+#             */
/*   Updated: 2022/09/16 13:24:44 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern	char **environ;

t_env	*env_node(void)
{
	t_env	*node;

	node = NULL;
	node = (t_env *)malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->key = NULL;
	node->val = NULL;
	node->next = NULL;
	return (node);
}

t_env	*env_init(t_env *env_head)
{
	t_env	*node;
	t_env	*prev;
	char	**ptr;
	
	node = NULL;
	prev = NULL;
	ptr = environ;
	node = env_node();
	env_head = node;
	while (*ptr)
	{
		if (prev)
			prev->next = node;
		node->key = ft_strdup(ft_strsep(ptr, "="));
		node->val = ft_strdup(*ptr);
		prev = node;
		ptr++;
		node = env_node();
	}
	return (env_head);
}