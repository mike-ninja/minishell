/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 11:44:19 by mbarutel          #+#    #+#             */
/*   Updated: 2022/10/07 09:21:12 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	dollar_swap_util(char **arg, char **env, t_dollar *attr)
{
	char	*extra;

	extra = get_extra(&attr->keys[attr->i]);
	find_match_env(arg, env, attr);
	if (!attr->match && !attr->i && !attr->key && !attr->needle)
		*arg = prefix(arg, attr->keys[attr->i]);
	if (extra)
	{
		if (attr->match)
			*arg = strjoin_head(*arg, extra);
		else
		{
			ft_strdel(arg);
			*arg = ft_strdup(extra);
		}
		ft_strdel(&extra);
	}
}

static void	dollar_struct(t_dollar *attr)
{
	attr->i = -1;
	attr->key = false;
	attr->keys = NULL;
	attr->match = false;
	attr->needle = false;
}

static char	*dollar_swap(char **arg, char **env)
{
	t_dollar	attr[1];

	dollar_struct(attr);
	if (arg[0][0] == '$')
		attr->key = true;
	attr->keys = ft_strsplit(*arg, '$');
	ft_memdel((void **)arg);
	while (attr->keys[++attr->i])
	{
		// ft_printf("- %s\n", attr->keys[attr->i]);
		dollar_swap_util(arg, env, attr);
		// ft_printf("~ %s\n", *arg);
		free(attr->keys[attr->i]);
	}
	free(attr->keys);
	return (*arg);
}

void	dollar_parse(t_session *sesh)
{
	int	i;

	i = -1;
	while (sesh->arg[++i])
	{
		if (!ft_strcmp(sesh->arg[i], "$$"))
		{
			ft_strdel(&sesh->arg[i]);
			sesh->arg[i] = ft_itoa(getpid());
		}	
		else if (ft_strchr(sesh->arg[i], '$') && (ft_strlen(sesh->arg[i]) > 1))
			sesh->arg[i] = dollar_swap(&sesh->arg[i], sesh->env);
	}
}
