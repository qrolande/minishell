/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_magic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrolande <qrolande@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 18:46:21 by qrolande          #+#    #+#             */
/*   Updated: 2022/01/17 19:37:05 by qrolande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	fd_work(t_shell *shell)
{
	if (shell->if_pipe > shell->num_pipe)
	{
		if (shell->num_pipe == 0)
			dup2(shell->fd[0][1], 1);
		else if (shell->if_pipe - 1 > shell->num_pipe)
		{
			dup2(shell->fd[shell->num_pipe -1][0], 0);
			dup2(shell->fd[shell->num_pipe][1], 1);
		}
		else if (shell->if_pipe - 1 == shell->num_pipe)
			dup2(shell->fd[shell->num_pipe - 1][0], 0);
	}
	// if (shell->her.if_heredoc)
	// 	dup2(shell->her.fd[0], 0);
	// if (shell->redir.r_num || shell->redir.l_num)
	// {
	// 	if (shell->redir.r_num)
	// 		dup2(shell->redir.r_fd, 1);
	// 	if (shell->redir.l_num)
	// 		dup2(shell->redir.r_fd, 0);
	// }
}

void	pipe_executor(char **env, t_shell *shell)
{
	char	*tmp_pipe;

	cleaning_company(shell, 2);
	tmp_pipe = ft_strdup(shell->temp[shell->num_pipe + 1]);
	tmp_pipe = prepare_cmd(tmp_pipe, 0, 0);
	cmd_parser(shell, tmp_pipe, -1, 0);
	shell->num_pipe += 1;
	cmd_executor(env, shell);
}