/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrolande <qrolande@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 17:15:13 by qrolande          #+#    #+#             */
/*   Updated: 2022/01/05 17:45:08 by qrolande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	check_quotes(char *line, int i)
{
	if (line[i] == '\'')
	{
		while (line[++i] != '\'' && line[i])
		{
			if (line[i] == '\\')
				i++;
		}
		if (!line[i])
			return (-1);
	}
	if (line[i] == '\"')
	{
		while (line[++i] != '\"' && line[i])
		{
			if (line[i] == '\\')
				i++;
		}
		if (!line[i])
			return (-1);
	}
	return (0);
}

static int	quotes_syntax(char *line)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if (line[i] == '\'' || line[i] == '\"')
		{
			if (check_quotes(line, i) == -1)
				return (-1);
		}	
		i++;
	}
	return (0);
}

static char	pipe_syntax(char *line, int i)
{
	while (line[i] == ' ')
		i++;
	if (line[i] == ';' || (line[i] == ';' && line[i + 1] == ';'))
		return (';');
	if (line[i] == '|')
		return ('|');
	return ('0');
}

static void	syntax(char *str)
{
	if (quotes_syntax(str) == -1)
	{
		printf("error: unclosed quotes\n");
		exit(EXIT_FAILURE);
	}
	if (pipe_syntax(str, 0) != '0')
	{
		printf("syntax error near unexpected token '%c'\n", \
			pipe_syntax(str, 0));
		exit(EXIT_FAILURE);
	}	
}

char	*prepare_cmd(char *str, t_shell *shell)
{
	shell->i = 0;
	syntax(str);
	str = if_space(str, shell);
	return (str);
}
