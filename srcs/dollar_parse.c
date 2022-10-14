/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 11:44:19 by mbarutel          #+#    #+#             */
/*   Updated: 2022/10/14 15:07:47 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	get_prefix(char **arg)
{
	int		len;
	char	*ret;

	len = 0;
	ret = NULL;
	while (arg[0][len] && arg[0][len] != '$')
		len++;
	if (arg[0][len] && len)
	{
		ret = (char *)ft_memalloc(sizeof(char) * (len + 1));
		ft_bzero((char *)ret, len + 1);
		len = -1;
		while (arg[0][++len] && arg[0][len] != '$')
			ret[len] = arg[0][len];
		ft_strdel(arg);
		*arg = ret;
	}
	else
		ft_strdel(arg);
}

static void	dollar_swap_util(char **arg, char **env, t_dollar *attr)
{
	char	*extra;

	if (!attr->i)
		get_prefix(arg);
	extra = get_extra(&attr->keys[attr->i]);
	find_match_env(arg, env, attr);
	if (extra)
	{
		*arg = strjoin_head(*arg, extra);
		ft_strdel(&extra);
	}
}

static void	dollar_struct(t_dollar *attr)
{
	attr->i = -1;
	attr->keys = NULL;
	attr->match = false;
}

static char	*dollar_swap(char **arg, char **env)
{
	char		*hay;
	t_dollar	attr[1];

	dollar_struct(attr);
	hay = ft_strchr(*arg, '$');
	if (hay)
		hay = ft_strdup(hay);
	attr->keys = ft_strsplit(*arg, '$');
	while (attr->keys[++attr->i])
	{
		if (hay && ft_strstr(hay, attr->keys[attr->i]))
			dollar_swap_util(arg, env, attr);
		ft_strdel(&attr->keys[attr->i]);
	}
	ft_strdel(&hay);
	ft_memdel((void **)attr->keys);
	return (*arg);
}

void	dollar_parse(t_session *sesh)
{
	int	i;

	i = -1;
	while (sesh->tokens->arg[++i])
	{
		if (!ft_strcmp(sesh->tokens->arg[i], "$$"))
		{
			ft_strdel(&sesh->tokens->arg[i]);
			sesh->tokens->arg[i] = ft_itoa(getpid());
		}
		else if (sesh->tokens->tok[i] && (ft_strlen(sesh->tokens->arg[i]) > 1))
		{
			sesh->tokens->arg[i] = dollar_swap(&sesh->tokens->arg[i], sesh->env);
		}
		if (!sesh->tokens->arg[i])
			sesh->tokens->arg[i] = ft_strdup("");
	}
}
