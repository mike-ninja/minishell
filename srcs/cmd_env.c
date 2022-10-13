/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 20:42:38 by mbarutel          #+#    #+#             */
/*   Updated: 2022/10/13 10:19:52 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**update_arg(t_session *sesh, char **arg)
{
	int		i;
	char	**new_arg;

	new_arg = (char **)malloc(sizeof(char *) * (array_len(arg, END) + 1));
	if (!new_arg)
		return (NULL);
	i = 0;
	while (arg[i])
	{
		new_arg[i] = ft_strdup(arg[i]);
		i++;
	}
	new_arg[i] = NULL;
	arg_clean(sesh->arg);
	return (new_arg);
}

// static int	set_tmp_env(t_session *sesh, int i)
// {
// 	char	*sep;
// 	char	*tofree;

// 	sep = NULL;
// 	cmd_setenv(sesh);
// 	sep = ft_strdup(sesh->arg[i]);
// 	tofree = sep;
// 	sesh->tmp_env = ft_strdup(ft_strsep(&sep, "="));
// 	ft_strdel(&tofree);
// 	return (++i);
// }

static void	alloc_tmp_en(char ***tm_en)
{
	int		i;
	int		len;
	char	**ret;

	i = -1;
	len = 0;
	if (!*tm_en)
	{
		ret = (char **)malloc(sizeof(char *) * 2);
		while (++i < 2)
			ret[i] = NULL;
		*tm_en = ret;
	}
	else
	{
		while (tm_en[0][len])
			len++;
		ret = (char **)malloc(sizeof(char *) * (len + 2)); // malloc fail exit check here
		ret[len] = NULL;
		i = -1;
		while (tm_en[0][++i])
			ret[i] = tm_en[0][i];
		while (++i < (len + 2))
			ret[i] = NULL;
		// ft_memdel((void **)*tm_en); // This causes double free, but how do we know it wont leak??
		*tm_en = ret;
	}
}

static int	set_tmp_env(t_session *sesh, int i)
{
	int		j;
	char	*sep;
	char	*tofree;
	char	*replaced;

	j = 0;
	sep = NULL;
	tofree = NULL;
	while (sesh->arg[i] && ft_strchr(sesh->arg[i], '=') && *sesh->arg[i] != '=')
	{
		alloc_tmp_en(&sesh->tm_en);
		if (!replace_value(sesh, ft_strdup(sesh->arg[i]), &replaced))
		{
			sep = ft_strdup(sesh->arg[i]);
			append_env(sesh, &sesh->arg[i]);
			tofree = sep;	
			sesh->tm_en[j++] = ft_strdup(ft_strsep(&sep, "="));
			ft_strdel(&tofree);
			
		}
		else
			sesh->tm_en[j++] = replaced;
		// ft_printf("%s\n", sesh->tm_en[j]);
		i++;
	}
	return (i);
}

int	cmd_env(t_session *sesh)
{
	int		i;
	char	**env;

	i = 1;
	if (sesh->arg[i] && ft_strchr(sesh->arg[i], '=')) // This needs to be worked on
		i = set_tmp_env(sesh, i);
	// char **art;

	// ft_printf("This happens\n");
	// art = sesh->tm_en;
	// while (*art)
	// {
	// 	ft_printf("[%s]\n", *art);
	// 	art++;
	// }
	// ft_printf("This happens\n");
	if (sesh->arg[i])
	{
		sesh->result = ERROR;
		sesh->arg = update_arg(sesh, &sesh->arg[i]);
		return (ERROR);
	}
	env = sesh->env;
	while (*env)
	{
		ft_printf("%s\n", *env);
		env++;
	}
	return (RESET);
}
