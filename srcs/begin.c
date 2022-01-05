/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   begin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrolande <qrolande@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 16:13:11 by qrolande          #+#    #+#             */
/*   Updated: 2022/01/05 17:27:46 by qrolande         ###   ########.fr       */
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

void	begin(t_shell *shell)
{
	int	i;

	if (ft_strlen(shell->line))
	{
		i = 0;
		shell->num_cmd = 1;
		add_history(shell->line);
		semicolon_check(shell);
		while (shell->num_cmd)
		{
			shell->splitted_cmd[i] = prepare_cmd(shell->splitted_cmd[i], shell);
			pipe_work(shell, i);
			printf ("line = %s\n", shell->splitted_cmd[i]);
			shell->num_cmd--;
			i++;
		}
	}
}
