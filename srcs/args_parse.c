/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 16:55:57 by mbarutel          #+#    #+#             */
/*   Updated: 2022/10/14 15:07:12 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	arg_qty(char *line)
{
	int		len;
	char	*line_cpy;
	char	*tofree;

	len = 0;
	line_cpy = ft_strdup(line);
	tofree = line_cpy;
	line_cpy = skip_whitespace(line_cpy);
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
		len++;
	}
	ft_strdel(&tofree);
	return (len);
}

static void	qoute_removal(char **arg)
{
	int		i;
	int		j;
	char	ptr[MAXARGLEN];

	i = 0;
	j = 0;
	ft_bzero(ptr, MAXARGLEN);
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

static void	collect_args(char **args, char **line, bool	*tok)
{
	int		i;
	char	*ptr;
	char	*tojoin;

	i = 0;
	ptr = *line;
	tojoin = NULL;
	ptr = skip_whitespace(ptr);
	while (ptr)
	{
		if (*ptr == '"')
		{
			ptr++;
			args[i++] = ft_strdup(ft_strsep(&ptr, "\""));
			tok[i - 1] = 1;
			if (*ptr && !ft_iswhitespace(*ptr))
			{
				tojoin = args[i - 1];
				args[i - 1] = ft_strjoin(args[i - 1], ft_strsep(&ptr, " "));
				ft_strdel(&tojoin);
			}
		}
		else if (*ptr == '\'')
		{
			ptr++;
			args[i++] = ft_strdup(ft_strsep(&ptr, "\'"));
			tok[i - 1] = 0;
			if (*ptr && !ft_iswhitespace(*ptr))
			{
				tojoin = args[i - 1];
				args[i - 1] = ft_strjoin(args[i - 1], ft_strsep(&ptr, " "));
				ft_strdel(&tojoin);
			}
		}
		else
		{
			args[i++] = ft_strdup(ft_strsep(&ptr, " "));
			tok[i - 1] = 1;
			if (ft_strchr(args[i - 1], '"') || ft_strchr(args[i - 1], '\''))
				qoute_removal(&args[i - 1]);
		}
		ptr = skip_whitespace(ptr);
	}
	args[i] = NULL;
}

int	get_args(t_session *sesh, char **line)
{
	int	len;

	len = arg_qty(*line);
	sesh->tokens->arg = (char **)malloc(sizeof(char *) * (len + 1));
	sesh->tokens->tok = (bool *)ft_memalloc(sizeof(bool) * (len));
	if (!sesh->tokens->arg)
		ft_exit_no_mem(1);
	collect_args(sesh->tokens->arg, line, sesh->tokens->tok);
	tilda_parse(sesh);
	dollar_parse(sesh);
	return (RESET);
}
