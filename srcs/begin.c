/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   begin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrolande <qrolande@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 16:13:11 by qrolande          #+#    #+#             */
/*   Updated: 2022/01/30 06:36:02 by qrolande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	check_quotes(char *str, int *i)
{
	if (str[*i] == '\"')
	{
		*i += 1;
		while (str[*i] != '\"')
			*i += 1;
	}
	if (str[*i] == '\'')
	{
		*i += 1;
		while (str[*i] != '\'')
			*i += 1;
	}
}

static void	semicolon_check(t_shell *shell, int i, int j, int y)
{
	char	*str;

	while (shell->line[i])
	{
		check_quotes(shell->line, &i);
		if (shell->line[i] == ';')
		{
			str = ft_substr(shell->line, y, i - y);
			shell->splitted_cmd = two_dimension_check(shell->splitted_cmd, \
				str, &j, 0);
			y = i + 1;
			shell->num_cmd += 1;
		}
		i++;
	}
	if (ft_strlen(shell->line) > y)
	{
		str = ft_substr(shell->line, y, ft_strlen(shell->line) - y);
		shell->splitted_cmd = two_dimension_check(shell->splitted_cmd, \
			str, &j, 0);
	}
}

static int	if_another_minishell(int *i, t_shell *shell)
{
	int	a;
	int	pid;

	pid = 0;
	a = 0;
	if (shell->splitted_cmd[*i][0] == '.')
	{
		signal(SIGINT, SIG_IGN);
		shell->cmd = ft_split(shell->splitted_cmd[*i], ' ');
		free(shell->splitted_cmd[*i]);
		pid = fork();
		if (pid == 0)
			execve(shell->cmd[0], shell->cmd, env_constructor(shell, 0, 0));
		waitpid(pid, &a, 0);
		signal(SIGINT, SIG_DFL);
		free(shell->cmd[0]);
		*i += 1;
		g_ex_flag = a / 256;
		return (1);
	}
	return (0);
}

void	begin(t_shell *shell, char **env, int i)
{
	shell->num_cmd = 1;
	add_history(shell->line);
	syntax(shell);
	if (shell->error == 0)
		semicolon_check(shell, 0, 0, 0);
	while (shell->num_cmd && shell->error == 0)
	{
		shell->splitted_cmd[i] = prepare_cmd(shell->splitted_cmd[i], 0);
		pipe_work(shell, i, 0);
		if (if_another_minishell(&i, shell))
		{
			free(shell->cmd);
			shell->cmd = NULL;
			break ;
		}
		cmd_parser(shell, shell->splitted_cmd[i], 0, 0);
		if (!shell->error)
			cmd_executor(env, shell, 0, 0);
		cleaning_company(shell, 1);
		shell->num_cmd -= 1;
		i++;
	}
	cleaning_company(shell, 3);
	shell->error = 0;
}
