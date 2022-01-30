/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_magic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrolande <qrolande@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 18:46:21 by qrolande          #+#    #+#             */
/*   Updated: 2022/01/30 06:36:37 by qrolande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	**split_for_pipe(t_shell *shell, char *str, int i, int j)
{
	int		y;
	char	**str_tmp;

	y = 0;
	str_tmp = (char **)malloc(sizeof(char *) * (shell->if_pipe + 1));
	while (str[++i])
	{
		check_quotes(str, &i);
		if (str[i] == '|')
		{
			i++;
			str_tmp[++j] = ft_substr(str, y, i - y - 1);
			y = i;
		}
	}
	if (shell->if_pipe > j)
		str_tmp[++j] = ft_strdup(str + y);
	str_tmp[++j] = NULL;
	return (str_tmp);
}

void	pipe_work(t_shell *shell, int i, int j)
{
	while (shell->splitted_cmd[i][j])
	{
		check_quotes(shell->splitted_cmd[i], &j);
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
			pipe(shell->fd[j]);
			j++;
		}
		shell->if_pipe += 1;
		shell->num_pipe = 0;
		shell->temp = split_for_pipe(shell, shell->splitted_cmd[i], -1, -1);
		free(shell->splitted_cmd[i]);
		shell->splitted_cmd[i] = ft_strdup(shell->temp[0]);
	}
}

static void	if_red_her(t_shell *shell)
{
	if (shell->her.if_heredoc)
		dup2(shell->her.fd[0], 0);
	if (shell->redir.r_num || shell->redir.l_num)
	{
		if (shell->redir.r_num)
			dup2(shell->redir.r_fd, 1);
		if (shell->redir.l_num)
			dup2(shell->redir.r_fd, 0);
	}
}

void	fd_work(t_shell *shell, int flag)
{
	if (flag == 0)
	{
		if (shell->if_pipe > shell->num_pipe && shell->num_pipe)
			close(shell->fd[shell->num_pipe - 1][1]);
	}
	if (flag == 1)
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
		if_red_her(shell);
	}
}

void	pipe_executor(char **env, t_shell *shell)
{
	char	*tmp_pipe;

	cleaning_company(shell, 2);
	tmp_pipe = ft_strdup(shell->temp[shell->num_pipe + 1]);
	tmp_pipe = prepare_cmd(tmp_pipe, 0);
	cmd_parser(shell, tmp_pipe, -1, 0);
	shell->num_pipe += 1;
	cmd_executor(env, shell, 0, 0);
}
