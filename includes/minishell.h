/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrolande <qrolande@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 16:08:07 by qrolande          #+#    #+#             */
/*   Updated: 2022/01/03 21:53:24 by qrolande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

typedef struct s_structenv
{
	char				*key;
	char				*value;
	struct s_structenv	*next;
	int					flag;
}				t_structenv;

typedef struct s_shell
{
	t_structenv			*env_mass;
	char				**full_path;
	char				**cmd;
	char				**splitted_cmd;
	char				**args;
	char				*line;
	int					num_cmd;
	struct s_shell		*next;
}				t_shell;

void	env_parser(t_shell *shell, char	**env);
void	if_space(t_shell *shell, int i);
void	prepare_cmd(t_shell *shell, int i);
void	begin(t_shell *shell);

#endif