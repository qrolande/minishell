/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   begin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrolande <qrolande@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 16:13:11 by qrolande          #+#    #+#             */
/*   Updated: 2022/01/12 20:13:17 by qrolande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	pipe_work(t_shell *shell, int i)
{
	int		j;

	j = 0;
	while (shell->splitted_cmd[i][j])
	{
		if (shell->splitted_cmd[i][j] == '|')
			shell->if_pipe += 1;
		j++;
	}
	j = 0;
	if (shell->if_pipe)
	{
		shell->fd = (int **)malloc(sizeof(int *) * shell->if_pipe);
		while (j < shell->if_pipe)
		{
			shell->fd[j] = (int *)malloc(sizeof(int) * 2);
			pipe(shell->fd[j++]);
		}
		shell->if_pipe += 1;
		shell->num_pipe = 0;
		shell->temp = ft_split(shell->splitted_cmd[i], '|');
		shell->splitted_cmd[i] = ft_strdup(shell->temp[0]);
	}
}

static void	semicolon_check(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->line[i])
	{
		if (shell->line[i] == ';')
			shell->num_cmd += 1;
		i++;
	}
	shell->splitted_cmd = ft_split(shell->line, ';');
}

static int	if_another_minishell(int *i, t_shell *shell)
{
	int	pid;

	pid = 0;
	if (shell->splitted_cmd[*i][0] == '.')
	{
		shell->cmd = ft_split(shell->splitted_cmd[*i], ' ');
		pid = fork();
		if (pid == 0)
			execve(shell->cmd[0], shell->cmd, env_constructor(shell, 0, 0));
		wait(NULL);
		*i += 1;
		return (1);
	}
	return (0);
}

void	begin(t_shell *shell, char **env)
{
	int	i;

	if (ft_strlen(shell->line))
	{
		i = 0;
		shell->num_cmd = 1;
		add_history(shell->line);
		syntax(shell);
		if (shell->error == 0)
			semicolon_check(shell);
		while (shell->num_cmd > 0 && shell->error == 0)
		{
			shell->splitted_cmd[i] = prepare_cmd(shell->splitted_cmd[i]);
			pipe_work(shell, i);
			if (if_another_minishell(&i, shell))
			{
				free(shell->cmd);
				shell->cmd = NULL;
				break ;
			}
			cmd_parser(shell, shell->splitted_cmd[i], -1, 0);
			cmd_executor(env, shell);
			//printf ("cmd[%d] = %s\n", i, shell->cmd[i]);
			//printf ("line = %s\n", shell->splitted_cmd[i]);
			cleaning_company(shell);
			shell->num_cmd--;
			i++;
		}
		// if (shell->splitted_cmd)
		// {
		// 	free(shell->splitted_cmd);
		// 	shell->splitted_cmd = NULL;
		// }
		shell->error = 0;
	}
}
