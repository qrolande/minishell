/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akatlyn <akatlyn@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 21:04:19 by akatlyn           #+#    #+#             */
/*   Updated: 2022/01/28 00:22:16 by akatlyn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../includes/minishell.h"

static int	cmd_len(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
		i++;
	return (i);
}

static void	echo_action(t_shell *shell, int i, int fd)
{
	while (shell->cmd[i])
	{
		if (!ft_strcmp(shell->cmd[i], "$?"))
			ft_putnbr_fd(g_ex_flag, fd);
		else
			ft_putstr_fd(shell->cmd[i], fd);
		if (i + 1 < cmd_len(shell->cmd))
			write(fd, " ", 1);
		i++;
	}
}

void	ft_echo(t_shell *shell, int i)
{
	int	n;
	int	fd;		

	n = 0;
	fd = 1;
	if (shell->redir.r_num || shell->redir.x_num)
		fd = shell->redir.r_fd;
	if (shell->if_pipe - 1 > shell->num_pipe)
		fd = shell->fd[shell->num_pipe][1];
	if (!shell->cmd[i])
	{
		write(fd, "\n", 1);
		return ;
	}
	if (!ft_strcmp(shell->cmd[i], "-n"))
	{
		n = 1;
		i++;
	}
	echo_action(shell, i, fd);
	if (n == 1)
		return ;
	write(fd, "\n", 1);
	g_ex_flag = 0;
}
