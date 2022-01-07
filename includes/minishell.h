/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrolande <qrolande@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 16:08:07 by qrolande          #+#    #+#             */
/*   Updated: 2022/01/07 20:12:46 by qrolande         ###   ########.fr       */
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
	char				**temp;
	char				**splitted_cmd;
	char				*line;
	int					**fd;
	int					i;
	int					num_cmd;
	int					num_pipe;
	int					if_pipe;
	int					error;
	struct s_shell		*next;
}				t_shell;

void	env_parser(t_shell *shell, char	**env);
void	syntax(t_shell *shell);
char	*prepare_cmd(char *str, t_shell *shell);
void	begin(t_shell *shell);
char	**env_constructor(t_shell *shell, int i, int j);
void	parser_cmd(t_shell *shell, char *str, int i, int j);
char	*gap(char *str, int *i);

#endif