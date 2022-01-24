/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrolande <qrolande@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 19:39:29 by qrolande          #+#    #+#             */
/*   Updated: 2022/01/19 23:05:11 by qrolande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*gap(char *str, int *i)
{
	char	*str_tmp[4];
	int		j;

	j = *i;
	while (str[++(*i)])
	{
		if (str[*i] == '\'')
			break ;
	}
	str_tmp[0] = ft_substr(str, 0, j);
	str_tmp[1] = ft_substr(str, j + 1, *i - j - 1);
	str_tmp[2] = ft_strdup(str + *i + 1);
	str_tmp[3] = ft_strjoin_free(str_tmp[0], str_tmp[1]);
	str_tmp[0] = ft_strjoin_free(str_tmp[3], str_tmp[2]);
	free(str);
	free(str_tmp[1]);
	free(str_tmp[2]);
	*i -= 1;
	return (str_tmp[0]);
}

char	*double_gap(char *str, int *i, t_shell *shell)
{
	char	*str_tmp[4];
	int		j;

	j = *i;
	str = finder(str, i, shell);
	str_tmp[0] = ft_substr(str, 0, j);
	str_tmp[1] = ft_substr(str, j + 1, *i - j - 1);
	str_tmp[2] = ft_strdup(str + *i + 1);
	str_tmp[3] = ft_strjoin_free(str_tmp[0], str_tmp[1]);
	str_tmp[0] = ft_strjoin_free(str_tmp[3], str_tmp[2]);
	free(str);
	free(str_tmp[1]);
	free(str_tmp[2]);
	*i -= 1;
	return (str_tmp[0]);
}

char	*slash(char *str, int *i)
{
	char	*str1;
	char	*str2;

	str1 = ft_substr(str, 0, *i);
	str2 = ft_strdup(str + *i + 1);
	str1 = ft_strjoin_free(str1, str2);
	free(str);
	*i += 1;
	return (str1);
}

char	*tilde(char *str, int *i, t_shell *shell)
{
	int		j;
	char	*str1;
	char	*str2;
	char	*str3;

	j = *i;
	str1 = ft_substr(str, 0, j);
	str2 = ft_strdup(str + j + 1);
	str3 = ft_strjoin_free(str1, shell->home);
	str1 = ft_strjoin_free(str3, str2);
	free(str2);
	free(str);
	return (str1);
}

char	*dollar(char *str, int *i, t_shell *shell)
{
	char	*str1;
	char	*str2;
	char	*tmp_key;
	int		j;

	j = *i;
	while (str[++(*i)])
	{
		if (str[*i] != '_' && !ft_isalnum((str[*i])))
			break ;
	}
	if (*i == j + 1)
		return (str);
	str1 = ft_substr(str, 0, j);
	tmp_key = ft_substr(str, j + 1, *i - j - 1);
	tmp_key = find_key_value(tmp_key, shell);
	str2 = ft_strdup(str + *i);
	str1 = ft_strjoin_free(str1, tmp_key);
	str1 = ft_strjoin_free(str1, str2);
	free(str);
	free(str2);
	*i -= 1;
	return (str1);
}
