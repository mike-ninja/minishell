/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 16:55:57 by mbarutel          #+#    #+#             */
/*   Updated: 2022/10/06 17:21:58 by mbarutel         ###   ########.fr       */
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
		else
			ft_strsep(&line_cpy, " ");
		line_cpy = skip_whitespace(line_cpy);
		len++;
	}
	free(tofree);
	return (len);
}

static void	qoute_removal(char **arg)
{
	int		i;
	int		j;
	char	ptr[MAXARGLEN];

	i = 0;
	j = 0;
	ft_bzero(ptr, MAXARGLEN + 1);
	while (arg[0][i])
	{	
		while (arg[0][i] == '"')
			i++;
		ptr[j++] = arg[0][i++];
	}
	ft_strdel(arg);
	*arg = ft_strdup(ptr);
}

static void	collect_args(char **args, char **line)
{
	int		i;
	char	*ptr;

	i = 0;
	ptr = *line;
	ptr = skip_whitespace(ptr);
	while (ptr)
	{
		if (*ptr == '"')
		{
			ptr++;
			args[i++] = ft_strdup(ft_strsep(&ptr, "\""));
		}
		else
		{
			args[i++] = ft_strdup(ft_strsep(&ptr, " "));
			if (ft_strchr(args[i - 1], '"'))
				qoute_removal(&args[i - 1]);
		}
		ptr = skip_whitespace(ptr);
	}
	args[i] = NULL;
	free(*line);
	*line = NULL;
}

int	get_args(t_session *sesh, char **line)
{
	sesh->arg = (char **)malloc(sizeof(char *) * (arg_qty(*line) + 1));
	if (!sesh->arg)
		return (ERR_NOMEM);
	collect_args(sesh->arg, line);
	tilda_parse(sesh);
	dollar_parse(sesh);
	return (RESET);
}
