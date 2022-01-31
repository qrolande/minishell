/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrolande <qrolande@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 21:19:57 by akatlyn           #+#    #+#             */
/*   Updated: 2022/01/30 08:12:48 by qrolande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../includes/minishell.h"

void	ft_env(t_shell	*shell, int fd)
{
	t_structenv	*tmp;

	tmp = shell->env_mass;
	if (shell->redir.r_num || shell->redir.x_num)
		fd = shell->redir.r_fd;
	if (shell->num_pipe < shell->if_pipe - 1)
		fd = shell->fd[shell->num_pipe][1];
	while (tmp)
	{
		if (shell->full_path == NULL)
		{
			env_error_msg(shell);
			return ;
		}
		if (tmp->key && tmp->equality)
		{
			ft_putstr_fd(tmp->key, fd);
			write(fd, "=", 1);
			if (tmp->value)
				ft_putstr_fd(tmp->value, fd);
			write(fd, "\n", 1);
		}
		tmp = tmp->next;
	}
	g_ex_flag = 0;
}
