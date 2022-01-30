/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_without_param.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrolande <qrolande@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 16:41:09 by qrolande          #+#    #+#             */
/*   Updated: 2022/01/30 01:42:01 by qrolande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	export_msg_out(t_structenv *tmp, int *i, int fd)
{
	if (tmp->flag == *i)
	{
		write(fd, "declare -x ", 11);
		ft_putstr_fd(tmp->key, fd);
		if (tmp->equality == 1)
			write(fd, "=\"", 2);
		if (tmp->value)
			ft_putstr_fd(tmp->value, fd);
		if (tmp->equality == 1)
			write(fd, "\"", 1);
		write(fd, "\n", 1);
		*i += 1;
	}
}

void	ft_export_without_param(t_shell *shell, int i, int j)
{
	int			fd;
	t_structenv	*tmp;

	fd = 1;
	tmp = shell->env_mass;
	if (shell->redir.r_num || shell->redir.x_num)
		fd = shell->redir.r_fd;
	if (shell->if_pipe - 1 > shell->num_pipe)
		fd = shell->fd[shell->num_pipe][1];
	while (i < env_size(shell, 0) + 1)
	{
		if (1000 < j)
		{
			j = 0;
			i++;
		}
		export_msg_out(tmp, &i, fd);
		tmp = tmp->next;
		if (tmp == NULL)
			tmp = shell->env_mass;
		j++;
	}
}
