/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrolande <qrolande@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 16:01:47 by qrolande          #+#    #+#             */
/*   Updated: 2022/01/30 07:43:27 by qrolande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*finder(char *str, int *i, t_shell *shell)
{
	while (str[++(*i)])
	{
		if (str[*i] == '\\' && (str[*i + 1] == '\"' \
			|| str[*i + 1] == '$' || str[*i + 1] == '\\'))
			str = slash(str, i);
		if (str[*i] == '$' && str[*i + 1] == '?')
			str = exsts(str, i);
		if (str[*i] == '$')
			str = dollar(str, i, shell);
		if (str[*i] == '\"')
			break ;
	}
	return (str);
}

char	*exsts(char *str, int *i)
{
	char	*str1;
	char	*str2;

	str1 = ft_substr(str, 0, *i);
	str2 = ft_itoa(g_ex_flag);
	str1 = ft_strjoin_free(str1, str2);
	free(str2);
	str2 = ft_strdup(str + *i + 2);
	str1 = ft_strjoin_free(str1, str2);
	free(str2);
	free(str);
	return (str1);
}

static char	*types(char *str, int *i, t_shell *shell)
{
	if (str[*i] == '\'')
		return (gap(str, i));
	else if (str[*i] == '\"')
		return (double_gap(str, i, shell));
	else if (str[*i] == '\\')
		return (slash(str, i));
	else if (str[*i] == '~')
		return (tilde(str, i, shell));
	else if (str[*i] == '$')
		return (dollar(str, i, shell));
	if (str[*i] == '$' && str[*i + 1] == '?')
		return (exsts(str, i));
	return (str);
}

static char	*red_her_parser(t_shell *shell, char *str, int i)
{
	while (str[i] && !shell->error)
	{
		if (str[i] == '\"' || str[i] == '\'')
		{
			i += 1;
			while (str[i] && (str[i] != '\"' || str[i] != '\''))
				i++;
		}
		if (str[i] == '<' && str[i + 1] == '<')
		{
			str = heredoc(shell, str, i, 0);
			i = -1;
		}
		else if (str[i] == '<' || str[i] == '>')
		{
			str = redirect(shell, str, i);
			i = -1;
		}
		i++;
	}
	return (str);
}

void	cmd_parser(t_shell *shell, char *str, int i, int j)
{
	int	res;

	res = 0;
	str = red_her_parser(shell, str, 0);
	while (str[i] && shell->error == 0)
	{
		str = types(str, &i, shell);
		if (str[i] == ' ')
		{
			shell->cmd = two_dimension_check(shell->cmd, \
				ft_substr(str, res, i - res), &j, 0);
			res = i + 1;
		}
		i++;
	}
	if (res != ft_strlen(str) && shell->error == 0)
	{
		shell->cmd = two_dimension_check(shell->cmd, \
			ft_substr(str, res, ft_strlen(str) - res), &j, 0);
	}
	free(str);
}
