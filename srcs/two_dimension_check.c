/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   two_dimension_check.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrolande <qrolande@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 19:17:57 by qrolande          #+#    #+#             */
/*   Updated: 2022/01/10 17:00:28 by qrolande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*find_key_value(char *tmp_key, t_shell *shell)
{
	int	res;

	res = ft_strlen(tmp_key);
	while (shell->env_mass)
	{
		if (!ft_strncmp(tmp_key, shell->env_mass->key, res))
			return (shell->env_mass->value);
		shell->env_mass = shell->env_mass->next;
	}
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
	}
	tmp_arr[i] = ft_strdup(str);
	tmp_arr[i + 1] = NULL;
	free(arr);
	free(str);
	*j += 1;
	return (tmp_arr);
}
