/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrolande <qrolande@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 19:32:03 by qrolande          #+#    #+#             */
/*   Updated: 2022/01/30 06:30:19 by qrolande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*heredoc2(t_shell *shell, char *ext, int i)
{
	char	*tmp;

	tmp = NULL;
	tmp = readline("> ");
	if (tmp && ft_strcmp(tmp, ext))
	{
		while (tmp[++i])
		{
			if (tmp[i] == '\\')
				tmp = slash(tmp, &i);
			if (tmp[i] == '$')
				tmp = dollar(tmp, &i, shell);
		}
		write(shell->her.fd[1], tmp, ft_strlen(tmp));
		write(shell->her.fd[1], "\n", 1);
		return (tmp);
	}
	else
	{
		free(tmp);
		return (NULL);
	}
}

static char	*heredoc_work(char *str, int i)
{
	char	*str1;
	char	*str2;

	while (str[i] != '<')
		i++;
	if (i > 0)
		str1 = ft_substr(str, 0, i - 1);
	else
		str1 = ft_strdup("");
	while (str[i] == '<' || str[i] == ' ')
		i++;
	while (str[i] && str[i] != ' ' && str[i] != '\t')
		i++;
	if (str[i])
		str2 = ft_strdup(str + i);
	else
		str2 = ft_strdup("");
	str1 = ft_strjoin_free(str1, str2);
	free(str2);
	free(str);
	str1 = prepare_cmd(str1, 0);
	return (str1);
}

int	check_ext(char *str)
{
	if (str[0] == '\0')
	{
		printf("minishell> syntax error near unexpected token `newline'\n");
		return (1);
	}
	return (0);
}

char	*heredoc(t_shell *shell, char *str, int i, int j)
{
	char	*str1;
	char	*ext;

	str1 = ft_strdup(" ");
	shell->her.if_heredoc = 1;
	pipe(shell->her.fd);
	while (str[i] && (str[i] == '<' || str[i] == ' '))
		i++;
	j = i;
	while (str[i] && str[i] != ' ' && str[j] != '\t')
		i++;
	ext = ft_substr(str, j, i - j);
	if (!check_ext(ext))
	{
		while (str1 && ft_strcmp(str1, ext))
		{
			free(str1);
			str1 = heredoc2(shell, ext, -1);
		}
		free(str1);
		close(shell->her.fd[1]);
		str1 = heredoc_work(str, 0);
	}
	free(ext);
	return (str1);
}
