/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrolande <qrolande@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 18:01:25 by qrolande          #+#    #+#             */
/*   Updated: 2022/01/23 15:47:19 by qrolande         ###   ########.fr       */
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

static char	*destroying_red(char *tmp_str, char *str, int j)
{
	char	*str1;
	char	*str2;
	char	*str3;

	if (j < ft_strlen(str))
		str2 = ft_strdup(str + j);
	else
		str2 = ft_strdup("");
	str3 = ft_strjoin_free(tmp_str, " ");
	str1 = ft_strjoin_free(str3, str2);
	free (str2);
	return (str1);
}

static char	*prepare_redir(t_shell *shell, char *str, int j, int flag)
{
	int		i;
	char	*file;
	char	*tmp_str;

	i = 0;
	if (j)
		tmp_str = ft_substr(str, 0, j - 1);
	else
		tmp_str = ft_strdup("");
	while (str[j] && (str[j] == ' ' || str[j] == '>' || str[j] == '<'))
		j++;
	i = j;
	while (str[j] && str[j] != ' ' && str[j] != '\t')
		j++;
	file = ft_substr(str, i, j - i);
	file_prepare(file, shell, flag);
	while (str[j] == ' ')
		j++;
	if (!shell->error)
		tmp_str = destroying_red(tmp_str, str, j);
	free(str);
	tmp_str = prepare_cmd(tmp_str, 0);
	return (tmp_str);
}

char	*redirect(t_shell *shell, char *str, int *i)
{
	int	j;
	int	flag;

	j = *i;
	flag = 0;
	if (str[j] == '<')
		flag = 1;
	if (str[j] == '>' && (!str[j + 1] || str[j + 1] != '>'))
		flag = 2;
	else
		flag = 3;
	if (flag)
		str = prepare_redir(shell, str, j, flag);
	return (str);
}
