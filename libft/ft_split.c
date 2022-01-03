/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrolande <qrolande@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 16:50:53 by qrolande          #+#    #+#             */
/*   Updated: 2022/01/03 16:50:54 by qrolande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	words_count(char const *s, char c)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	while (s[i] != '\0')
	{
		if ((s[i] != c) && (s[i + 1] == c || s[i + 1] == '\0'))
			res++;
		i++;
	}
	return (res);
}

static int	word_lenght(char const *s, char c, int j)
{
	int	len;

	len = 0;
	while (s[j] != c && s[j] != '\0')
	{
		len++;
		j++;
	}
	return (len);
}

static void	*freemem(char **result, int i)
{
	int	a;

	a = 0;
	while (a < i)
	{
		free(result[a]);
		a++;
	}
	free(result);
	return (NULL);
}

static char	**arr_res(char const *s, int res_word, char c, char **result)
{
	int	len;
	int	i;
	int	j;
	int	a;

	i = 0;
	j = 0;
	while (i < res_word)
	{
		while (s[j] == c)
			j++;
		len = word_lenght(s, c, j);
		result[i] = (char *)malloc(sizeof(char) * (len + 1));
		if (result[i] == NULL)
			return (freemem(result, i));
		a = 0;
		while (len > a)
			result[i][a++] = s[j++];
		result[i++][a] = '\0';
	}
	result[i] = NULL;
	return (result);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		res_word;

	if (s == NULL)
		return (NULL);
	res_word = words_count(s, c);
	result = (char **)malloc(sizeof(char *) * (res_word + 1));
	if (result == NULL)
		return (NULL);
	result = arr_res(s, res_word, c, result);
	return (result);
}
