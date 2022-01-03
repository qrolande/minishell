/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrolande <qrolande@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 17:15:13 by qrolande          #+#    #+#             */
/*   Updated: 2022/01/03 21:44:11 by qrolande         ###   ########.fr       */
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
	if (line[i] == ';')
		return (';');
	if (line[i] == '|')
		return ('|');
	return ('0');
}

void	prepare_cmd(t_shell *shell, int i)
{
	if (quotes_syntax(shell->splitted_cmd[i]) == -1)
	{
		printf("error: unclosed quotes\n");
		exit(EXIT_FAILURE);
	}
	if (pipe_syntax(shell->splitted_cmd[i], 0) != '0')
	{
		printf("syntax error near unexpected token '%c'\n", \
			pipe_syntax(shell->splitted_cmd[i], 0));
		exit(EXIT_FAILURE);
	}
	if_space(shell, i);
}
