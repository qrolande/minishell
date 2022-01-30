/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrolande <qrolande@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 20:54:24 by akatlyn           #+#    #+#             */
/*   Updated: 2022/01/30 06:48:39 by qrolande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*set_old_pwd(t_shell	*shell)
{
	char		*buf;
	t_structenv	*tmp;

	tmp = shell->env_mass;
	while (tmp)
	{
		if (!ft_strcmp("OLDPWD", tmp->key))
			buf = ft_strdup(tmp->value);
		tmp = tmp->next;
	}
	if (!buf)
	{
		write(2, "minishell: cd: OLDPWD not set\n", 15);
		shell->error++;
	}
	return (buf);
}

static void	choice_way(t_shell *shell, char **line)
{
	if (!shell->cmd[1])
		*line = ft_strjoin(shell->home, "/");
	else if (!ft_strcmp(shell->cmd[1], "-"))
	{
		*line = set_old_pwd(shell);
		if (*line)
		{
			write(2, *line, ft_strlen(*line));
			write(2, "\n", 1);
		}
	}
	else if (shell->cmd[1])
		*line = ft_strdup(shell->cmd[1]);
}

static void	swap_pwd(char *anypwd, t_shell *shell, char *where)
{
	t_structenv	*tmp;

	tmp = shell->env_mass;
	while (tmp)
	{
		if (!strcmp(anypwd, tmp->key))
		{
			free(tmp->value);
			tmp->value = NULL;
			tmp->value = ft_strdup(where);
		}
		tmp = tmp->next;
	}
}

static void	swap_way(t_shell *shell, char *line)
{
	char	*buf;

	buf = malloc(1000);
	getcwd(buf, 1000);
	swap_pwd("OLDPWD", shell, buf);
	if (line)
		if (chdir(line) == -1)
			ft_putstr_fd(strerror(errno), 2);
	getcwd(buf, 1000);
	swap_pwd("PWD", shell, buf);
	free(buf);
}

void	ft_cd(t_shell	*shell)
{
	DIR		*way;
	char	*line;

	way = NULL;
	choice_way(shell, &line);
	if (line)
		way = opendir(line);
	if (shell->error || way == NULL)
	{
		if (way == NULL)
		{
			ft_putstr_fd(strerror(errno), 2);
			write(2, "\n", 1);
		}
		free(line);
		g_ex_flag = 1;
		return ;
	}
	swap_way(shell, line);
	closedir(way);
	free(line);
	g_ex_flag = 0;
}
