/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_parse_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 16:39:30 by mbarutel          #+#    #+#             */
/*   Updated: 2022/10/17 13:29:58 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	arg_qty_loop(char *line_cpy, int *len)
{
	while (line_cpy)
	{
		if (*line_cpy == '"')
		{
			line_cpy++;
			ft_strsep(&line_cpy, "\"");
		}
		else if (*line_cpy == '\'')
		{
			line_cpy++;
			ft_strsep(&line_cpy, "\'");
		}
		else
			ft_strsep(&line_cpy, " ");
		line_cpy = skip_whitespace(line_cpy);
		len[0]++;
	}
}

static void	qoute_removal(char **arg)
{
	int		i;
	int		j;
	char	ptr[BUFF_SIZE];

	i = 0;
	j = 0;
	ft_bzero(ptr, BUFF_SIZE);
	while (arg[0][i])
	{	
		while (arg[0][i] && (arg[0][i] == '"' || arg[0][i] == '\''))
			i++;
		ptr[j++] = arg[0][i++];
		while (arg[0][i] && (arg[0][i] == '"' || arg[0][i] == '\''))
			i++;
	}
	ft_strdel(arg);
	*arg = ft_strdup(ptr);
}

static void	qoute_parse(char **ptr, char **arg, int *i, char *sep)
{
	char	*tojoin;

	tojoin = NULL;
	ptr[0]++;
	arg[i[0]++] = ft_strdup(ft_strsep(&ptr[0], sep));
	if (ptr[0] && !ft_iswhitespace(ptr[0][0]))
	{
		tojoin = arg[i[0] - 1];
		arg[i[0] - 1] = ft_strjoin(arg[i[0] - 1], ft_strsep(ptr, " "));
		ft_strdel(&tojoin);
	}
}

void	collect_args_loop(char **args, char *ptr, bool *tok, int *i)
{
	while (ptr)
	{
		if (*ptr == '"')
		{
			tok[*i] = 1;
			qoute_parse(&ptr, args, i, "\"");
		}
		else if (*ptr == '\'')
		{
			tok[*i] = 0;
			qoute_parse(&ptr, args, i, "\'");
		}
		else
		{
			args[i[0]++] = ft_strdup(ft_strsep(&ptr, " "));
			tok[*i - 1] = 1;
			if (ft_strchr(args[*i - 1], '"') || ft_strchr(args[*i - 1], '\''))
				qoute_removal(&args[*i - 1]);
		}
		ptr = skip_whitespace(ptr);
	}
	args[*i] = NULL;
}
