/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 11:44:19 by mbarutel          #+#    #+#             */
/*   Updated: 2022/10/01 22:58:55 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*forge_arg(char **arg, char *str)
{
	if (!*arg)
		*arg = ft_strdup(str);
	else
		*arg = strjoin_head(*arg, str);
	return (*arg);
}

static int	break_string(int i, char *str)
{
	if (!i)
	{
		while (str[i] != '=')
			i++;
		str[i] = '\0';
	}
	else
		str[i] = '=';
	return (i);
}

static char	*get_tail(char **keys)
{
	int		i;
	char	*ptr;

	i = 0;
	while (keys[0][i] && (ft_isalpha(keys[0][i]) && ft_isalnum(keys[0][i])))
		i++;
	if (keys[0][i])
	{
		ptr = ft_strdup(&keys[0][i]);
		keys[0][i] = '\0';
		// ft_printf("%c]]\n", keys[0][i]); // Continue from here
		return(ptr);
	}
	else
		return (NULL);
}

static char	**dollar_swap(char **arg, char **env, char *input)
{
	int			i;
	int			j;
	char		**ptr;
	char		**keys;
	char		*tail;

	tail = NULL;
	keys = ft_strsplit(input, '$');
	ft_memdel((void **)arg);
	j = -1;
	while (keys[++j])
	{
		ptr = env;
		tail = get_tail(keys);
		while (ptr[0])
		{
			i = break_string(0, ptr[0]);
			if (ft_strcmp(ptr[0], keys[j]) == 0)
			{
				*arg = forge_arg(arg, &ptr[0][i + 1]);
				break_string(i, ptr[0]);
				break ;
			}
			break_string(i, ptr[0]);
			ptr++;
		}
		if (!ptr[0] && !j && *input != '$')
			*arg = forge_arg(arg, *keys);
		if (tail)
		{
			*arg = strjoin_head(*arg, tail);
			ft_strdel(&tail);
		}
		free(keys[j]);
	}
	free(keys);
	return (arg);
}

// static char	**dollar_swap(char **arg, char **env, char *input)
// {
// 	int			i;
// 	int			j;
// 	char		**keys;
// 	char		**ptr;

// 	keys = ft_strsplit(input, '$');
// 	ft_memdel((void **)arg);
// 	j = -1;
// 	while (keys[++j])
// 	{
// 		ptr = env;
// 		while (ptr[0])
// 		{
// 			i = 0;
// 			while (ptr[0][i] != '=')
// 				i++;
// 			ptr[0][i] = '\0';
// 			if (ft_strcmp(ptr[0], keys[j]) == 0)
// 			{
// 				if (!*arg)
// 					*arg = ft_strdup(&ptr[0][i + 1]);
// 				else
// 					*arg = strjoin_head(*arg, &ptr[0][i + 1]);
// 				ptr[0][i] = '=';
// 				break ;
// 			}
// 			ptr[0][i] = '=';
// 			ptr++;
// 		}
// 		if (!ptr[0] && !j && *input != '$')
// 		{
// 			if (!*arg)
// 				*arg = ft_strdup(*keys);
// 			else
// 				*arg = strjoin_head(*arg, *keys);
// 		}
// 		free(keys[j]);
// 	}
// 	free(keys);
// 	return (arg);
// }

char	**dollar_parse(t_session *sesh)
{
	char	**arg;

	arg = sesh->arg;
	while (*sesh->arg)
	{
		if (ft_strchr(*sesh->arg, '$') && (ft_strlen(*sesh->arg) > 1))
			sesh->arg = dollar_swap(sesh->arg, sesh->env, *sesh->arg);
		sesh->arg++;
	}
	return (arg);
}
