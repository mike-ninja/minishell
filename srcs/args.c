/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 16:55:57 by mbarutel          #+#    #+#             */
/*   Updated: 2022/09/29 13:51:13 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	get_qoute_position(char *line, int i)
{
	i++;
	while (line[i] != '"' && line[i])
		i++;
	return (i);
}

static int	arg_qty(char *line)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '"')
		{
			len++;
			i = get_qoute_position(line, i);
		}
		if (line[i] != ' ' && i == 0)
				len++;
		if (i)
			if (line[i] != ' ' && line[i - 1] == ' ')
				len++;
		i++;
	}
	return (len);
}

static char	*skip_whitespace(char *str)
{
	if (str)
	{
		while (*str)
		{
			if (!ft_iswhitespace(*str))
				return (str);
			str++;
		}	
	}
	return (NULL);
}

static char	**collect_args(char **args, char **line)
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
			args[i++] = ft_strdup(ft_strsep(&ptr, " "));
		ptr = skip_whitespace(ptr);
	}
	args[i] = NULL;
	free(*line);
	*line = NULL;
	return (args);
}

// static void	print_args(char **arg)
// {
// 	while (*arg)
// 	{
// 		ft_printf("%s\n", *arg);
// 		arg++;
// 	}
// }env -

char	**get_args(t_session *sesh, char **line)
{
	sesh->arg = (char **)malloc(sizeof(char *) * (arg_qty(*line) + 1));
	if (!sesh->arg)
		return (NULL);
	sesh->arg = collect_args(sesh->arg, line);
	sesh->arg = dollar_parse(sesh);
	sesh->arg = tilda_parse(sesh);
	return (sesh->arg);
}
