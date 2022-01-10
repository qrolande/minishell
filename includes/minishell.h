/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrolande <qrolande@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 16:08:07 by qrolande          #+#    #+#             */
/*   Updated: 2022/01/10 19:08:58 by qrolande         ###   ########.fr       */
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

void	syntax(t_shell *shell);
char	*prepare_cmd(char *str);
char	*gap(char *str, int *i);
char	*slash(char *str, int *i);
void	begin(t_shell *shell, char **env);
void	env_parser(t_shell *shell, char	**env);
void	cmd_executor(char **env, t_shell *shell);
char	*tilde(char *str, int *i, t_shell *shell);
char	*dollar(char *str, int *i, t_shell *shell);
char	*dollar(char *str, int *i, t_shell *shell);
char	*double_gap(char *str, int *i, t_shell *shell);
char	*find_key_value(char *tmp_key, t_shell *shell);
char	**env_constructor(t_shell *shell, int i, int j);
void	cmd_parser(t_shell *shell, char *str, int i, int j);
char	**two_dimension_check(char	**arr, char *str, int *j, int i);

#endif