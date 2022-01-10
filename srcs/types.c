/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrolande <qrolande@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 19:39:29 by qrolande          #+#    #+#             */
/*   Updated: 2022/01/10 18:35:31 by qrolande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*gap(char *str, int *i)
{
	char	*str1;
	char	*str2;
	char	*str3;
	int		j;

	j = *i;
	while (str[++(*i)])
	{
		if (str[*i] == '\'')
			break ;
	}
	str1 = ft_substr(str, 0, j);
	str2 = ft_substr(str, j + 1, *i - j - 1);
	str3 = ft_strdup(str + *i + 1);
	str1 = ft_strjoin(str1, str2);
	str1 = ft_strjoin(str1, str3);
	free(str);
	*i -= 1;
	return (str1);
}

char	*double_gap(char *str, int *i, t_shell *shell)
{
	char	*str1;
	char	*str2;
	char	*str3;
	int		j;

	j = *i;
	while (str[++(*i)])
	{
		if (str[*i] == '\\' && (str[*i + 1] == '\"' \
			|| str[*i + 1] == '$' || str[*i + 1] == '\\'))
			str = slash(str, i);
		if (str[*i] == '$')
			str = dollar(str, i, shell);
		if (str[*i] == '\'')
			break ;
	}
	str1 = ft_substr(str, 0, j);
	str2 = ft_substr(str, j + 1, *i - j - 1);
	str3 = ft_strdup(str + *i + 1);
	str1 = ft_strjoin(str1, str2);
	str1 = ft_strjoin(str1, str3);
	free(str);
	*i -= 2;
	return (str1);
}

char	*slash(char *str, int *i)
{
	char	*str1;
	char	*str2;

	str1 = ft_substr(str, 0, *i);
	str2 = ft_strdup(str + *i + 1);
	str1 = ft_strjoin(str1, str2);
	free(str);
	*i += 1;
	return (str1);
}

char	*tilde(char *str, int *i, t_shell *shell)
{
	char	*str1;
	char	*str2;
	int		j;

	j = *i;
	str1 = ft_substr(str, 0, j);
	while (ft_strncmp(shell->env_mass->key, \
			"HOME", ft_strlen(shell->env_mass->key)))
		shell->env_mass = shell->env_mass->next;
	str2 = ft_strdup (str + j + 1);
	str1 = ft_strjoin(str1, shell->env_mass->value);
	str1 = ft_strjoin(str1, str2);
	free(str);
	*i += ft_strlen(shell->env_mass->value);
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
		if (str[*i] != '_' || !ft_isalnum((str[*i])))
			break ;
	}
	if (*i == j + 1)
		return (str);
	str1 = ft_substr(str, 0, j);
	tmp_key = ft_substr(str, j + 1, *i - j - 1);
	tmp_key = find_key_value(tmp_key, shell);
	str2 = ft_strdup(str + *i);
	str1 = ft_strjoin(str1, tmp_key);
	str1 = ft_strjoin(str1, str2);
	free(str);
	*i -= 1;
	return (str1);
}
