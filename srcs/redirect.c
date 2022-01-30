/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrolande <qrolande@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 18:01:25 by qrolande          #+#    #+#             */
/*   Updated: 2022/01/30 07:43:19 by qrolande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	file_prepare2(char *file, t_shell *shell, int flag, int fd)
{
	if (flag == 3)
	{
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (shell->redir.r_num == 0)
			shell->redir.r_num = 1;
		else
			close(shell->redir.r_fd);
		shell->redir.r_fd = fd;
	}
	if (fd < 0)
	{
		printf("minishell> %s: %s\n", file, strerror(errno));
		shell->error += 1;
		g_ex_flag = 1;
	}
}

static void	file_prepare(char *file, t_shell *shell, int flag)
{
	int	fd;

	fd = 0;
	if (flag == 1)
	{
		fd = open(file, O_RDONLY, 0644);
		if (shell->redir.l_num == 0)
			shell->redir.l_num = 1;
		else
			close(shell->redir.l_fd);
		shell->redir.l_fd = fd;
	}
	if (flag == 2)
	{
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (shell->redir.r_num == 0)
			shell->redir.r_num = 1;
		else
			close(shell->redir.r_fd);
		shell->redir.r_fd = fd;
	}
	file_prepare2(file, shell, flag, fd);
}

static char	*destroying_red(char *tmp_str, char *str, int i)
{
	char	*str1;
	char	*str2;
	char	*str3;

	if (i < ft_strlen(str))
		str2 = ft_strdup(str + i);
	else
		str2 = ft_strdup("");
	str1 = ft_strjoin_free(tmp_str, str2);
	free (str2);
	return (str1);
}

static char	*prepare_redir(t_shell *shell, char *str, int i, int flag)
{
	int		j;
	char	*file;
	char	*tmp_str;

	if (i > 0)
		tmp_str = ft_substr(str, 0, i - 1);
	else
		tmp_str = ft_strdup("");
	while (str[i] && (str[i] == ' ' || str[i] == '>' || str[i] == '<'))
		i++;
	j = i;
	while (str[i] && str[i] != ' ' && str[i] != '\t')
		i++;
	file = ft_substr(str, j, i - j);
	if (!g_ex_flag)
		file_prepare(file, shell, flag);
	while (str[i] == ' ')
		i++;
	if (!shell->error)
		tmp_str = destroying_red(tmp_str, str, i);
	free(str);
	free(file);
	return (tmp_str);
}

char	*redirect(t_shell *shell, char *str, int i)
{
	int	flag;

	flag = 0;
	if (str[i] == '<')
		flag = 1;
	else if (str[i] == '>' && (!str[i + 1] || str[i + 1] != '>'))
		flag = 2;
	else
		flag = 3;
	if (flag > 0)
	{
		str = prepare_redir(shell, str, i, flag);
	}
	str = prepare_cmd(str, 0);
	return (str);
}
