/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning_company.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrolande <qrolande@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 20:56:42 by qrolande          #+#    #+#             */
/*   Updated: 2022/01/24 21:27:02 by qrolande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	clean_other(t_shell *shell)
{
	if (shell->redir.r_num)
	{
		close(shell->redir.r_fd);
		shell->redir.r_num = 0;
	}
	if (shell->redir.l_num)
	{
		close(shell->redir.l_fd);
		shell->redir.l_num = 0;
	}
	if (shell->her.if_heredoc)
	{
		shell->her.if_heredoc = 0;
		close(shell->her.fd[0]);
	}
}

static void	clean_pipe(t_shell *shell, int i)
{
	if (shell->temp)
	{
		while (shell->temp[++i])
			free(shell->temp[i]);
		free(shell->temp);
		shell->temp = NULL;
	}
	i = 0;
	if (shell->fd)
	{
		while (i < shell->if_pipe - 1)
		{
			close(shell->fd[i][0]);
			close(shell->fd[i][1]);
			free(shell->fd[i]);
			i++;
		}
		free(shell->fd);
		shell->fd = NULL;
	}
	shell->num_pipe = 1000;
	shell->if_pipe = 0;
}

static void	clean_cmd(t_shell *shell, int i)
{
	if (shell->cmd)
	{
		while (shell->cmd[++i])
			free(shell->cmd[i]);
		free(shell->cmd);
		shell->cmd = NULL;
	}
	i = 0;
	if (shell->full_path)
	{
		while (shell->full_path[i])
		{
			free(shell->full_path[i]);
			i++;
		}
		free(shell->full_path);
		shell->full_path = NULL;
	}
}

void	cleaning_company(t_shell *shell, int flag)
{
	if (flag == 1)
	{
		clean_cmd(shell, -1);
		clean_pipe(shell, -1);
		clean_other(shell);
	}
	if (flag == 2)
		clean_cmd(shell, -1);
	if (flag == 3)
	{
		if (shell->splitted_cmd)
		{
			free(shell->splitted_cmd);
			shell->splitted_cmd = NULL;
		}
	}
}
