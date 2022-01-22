/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrolande <qrolande@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 18:01:25 by qrolande          #+#    #+#             */
/*   Updated: 2022/01/22 18:44:03 by qrolande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*prepare_redir(t_shell *shell, char *str, int j, int flag)
{
	int		i;
	char	*file;
	char	*tmp_str;

	if (j)
		tmp_str = ft_substr(str, 0, j - 1);
	else
		tmp_str = ft_strdup("");
	
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