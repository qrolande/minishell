/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrolande <qrolande@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 14:08:08 by qrolande          #+#    #+#             */
/*   Updated: 2022/01/10 22:29:51 by qrolande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	quotes_syntax(char *line)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if (line[i] == '\'')
		{
			while (line[++i] != '\'' && line[i])
				if (line[i] == '\\')
					i++;
			if (!line[i])
				return (-1);
		}
		if (line[i] == '\"')
		{
			while (line[++i] != '\"' && line[i])
				if (line[i] == '\\')
					i++;
			if (!line[i])
				return (-1);
		}
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

static void	if_double_semicolons(t_shell *shell, int i)
{
	while (shell->line[i + 1])
	{
		if (shell->line[i] == ';' && shell->line[i + 1] == ';')
		{
			shell->error += 1;
			printf("minishell: syntax error near unexpected token ';;'\n");
		}
		i++;
	}
}

void	syntax(t_shell *shell)
{
	if_double_semicolons(shell, 0);
	if (quotes_syntax(shell->line) == -1)
	{
		shell->error += 1;
		printf("error: unclosed quotes\n");
	}
	if (pipe_syntax(shell->line, 0) != '0')
	{
		shell->error += 1;
		printf("syntax error near unexpected token '%c'\n", \
			pipe_syntax(shell->line, 0));
	}
}
