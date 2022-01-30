/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   two_dimension_check.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrolande <qrolande@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 19:17:57 by qrolande          #+#    #+#             */
/*   Updated: 2022/01/30 06:27:19 by qrolande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*find_key_value(char *tmp_key, t_shell *shell)
{
	int			res;
	t_structenv	*tmp_env;

	tmp_env = shell->env_mass;
	res = ft_strlen(tmp_key);
	while (tmp_env)
	{
		if (!ft_strncmp(tmp_key, tmp_env->key, res))
		{
			free(tmp_key);
			return (tmp_env->value);
		}
		tmp_env = tmp_env->next;
	}
	free(tmp_key);
	return ("");
}

char	**two_dimension_check(char	**arr, char *str, int *j, int i)
{
	char	**tmp_arr;

	tmp_arr = (char **)malloc(sizeof(char *) * (*j + 2));
	if (arr)
	{
		while (arr[i])
		{
			tmp_arr[i] = ft_strdup(arr[i]);
			free(arr[i]);
			i++;
		}
		free(arr);
	}
	tmp_arr[i] = ft_strdup(str);
	tmp_arr[i + 1] = NULL;
	free(str);
	*j += 1;
	return (tmp_arr);
}
