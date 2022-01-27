/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akatlyn <akatlyn@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 21:04:19 by akatlyn           #+#    #+#             */
/*   Updated: 2022/01/28 00:21:50 by akatlyn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../includes/minishell.h"

void	ft_pwd(t_shell *shell)
{
	char	*line;
	int		fd;

	fd = 1;
	if (shell->redir.r_num || shell->redir.x_num)
		fd = shell->redir.r_fd;
	if (shell->if_pipe - 1 > shell->num_pipe)
		fd = shell->fd[shell->num_pipe][1];
	line = malloc(1000);
	getcwd(line, 1000);
	if (!line)
	{
		perror("Reading path error\n");
		g_ex_flag = 1;
		return ;
	}
	else
	{
		ft_putstr_fd(line, fd);
		write(fd, "\n", 1);
	}
	free(line);
	g_ex_flag = 0;
}
